#define BLYNK_TEMPLATE_ID "TMPL604trFSYf"
#define BLYNK_TEMPLATE_NAME "Smart Garage Door"
#define BLYNK_AUTH_TOKEN "5f1SXK5wjA6aBmoeGBbEP82Q-dwE1KFE"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Wi-Fi dan Blynk
const char* ssid = "Wi-Fi";
const char* password = "zaidan12";
const char* blynk_auth = BLYNK_AUTH_TOKEN;

// Pin
#define IR_SENSOR_PIN 34
#define SERVO_PIN 18
#define LED_MERAH 17
#define LED_HIJAU 16
#define BUTTON_PIN 23 

// Blynk Virtual Pin
#define VPIN_DOOR_STATUS V0
#define VPIN_MANUAL_CONTROL V1
#define VPIN_LED_GREEN V3 
#define VPIN_LED_RED V4   

// Variable
Servo garageServo;                  // Servo
SemaphoreHandle_t servoSemaphore;
QueueHandle_t taskQueue; 
bool isDoorOpen = false;            // Status pintu
volatile bool ignoreSensor = false; // Pause read sensor
TimerHandle_t sensorTimer;          // Software timer

// Prototipe Functions
void handleQueueCommand(void* parameter);
void checkPhysicalButtonTask(void* parameter);
void IRsensorCallback(TimerHandle_t xTimer);
void IRsensorInterrupt();

// Input button dari Blynk
BLYNK_WRITE(VPIN_MANUAL_CONTROL) {
  int command = param.asInt(); // 1 untuk buka, 0 untuk tutup
  xQueueSend(taskQueue, &command, portMAX_DELAY); // Kirim perintah ke queue

  if (command == 1){
    ignoreSensor = true;  // Aktifkan abaikan sensor saat perintah manual
  } else if (command == 0){
    ignoreSensor = false;  // Aktifkan abaikan sensor saat perintah manual
  }
  IRsensorInterrupt();  // Trigger interrupt untuk mematikan sensor sementara
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_HIJAU, OUTPUT);
  pinMode(LED_MERAH, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(IR_SENSOR_PIN, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");
  Blynk.begin(blynk_auth, ssid, password);

  garageServo.attach(SERVO_PIN, 500, 2500);
  garageServo.write(0);  // Pintu tertutup

  servoSemaphore = xSemaphoreCreateBinary();
  taskQueue = xQueueCreate(10, sizeof(int));
  if (servoSemaphore == NULL || taskQueue == NULL) {
    Serial.println("Error creating semaphore or queue");
    while (true);
  }

  xSemaphoreGive(servoSemaphore);

  // Task untuk membaca perintah dari queue
  xTaskCreate(handleQueueCommand, "Handle Queue", 8192, NULL, 2, NULL);

  // Task untuk membaca tombol fisik
  xTaskCreate(checkPhysicalButtonTask, "Check Physical Button", 8192, NULL, 1, NULL);

  // Inisialisasi software timer untuk membaca sensor IR
  sensorTimer = xTimerCreate("SensorTimer", pdMS_TO_TICKS(2000), pdTRUE, NULL, IRsensorCallback);
  if (sensorTimer != NULL) {
    xTimerStart(sensorTimer, 0); // Mulai timer
  } else {
    Serial.println("Error creating software timer");
  }
}

void loop() {
  Blynk.run();
}

// Meng-handle queue berdasarkan input yang diterima
void handleQueueCommand(void* parameter) {
  int command;
  while (1) {
    if (xQueueReceive(taskQueue, &command, portMAX_DELAY)) {
      if (xSemaphoreTake(servoSemaphore, portMAX_DELAY)) {
        if (command == 1) {  // Buka pintu
          garageServo.write(90); // Buka pintu
          isDoorOpen = true;
          ignoreSensor = true; // Pause sensor
          digitalWrite(LED_MERAH, LOW);
          digitalWrite(LED_HIJAU, HIGH);
          Serial.println("Garasi terbuka.");
        } else {  // Tutup pintu
          garageServo.write(0); // Tutup pintu
          isDoorOpen = false;
          ignoreSensor = false; // Start sensor
          digitalWrite(LED_MERAH, HIGH);
          digitalWrite(LED_HIJAU, LOW);
          Serial.println("Garasi tertutup.");
        }
        Blynk.virtualWrite(VPIN_DOOR_STATUS, isDoorOpen ? 1 : 0);
        Blynk.virtualWrite(VPIN_MANUAL_CONTROL, isDoorOpen ? HIGH : LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
        xSemaphoreGive(servoSemaphore);
      }
    }
  }
}

// Membaca IR sensor menggunakan software timer
void IRsensorCallback(TimerHandle_t xTimer) {
  if (!ignoreSensor) { // Pause sensor
    int distance = analogRead(IR_SENSOR_PIN);  // Jarak
    Serial.printf("IR sensor: %d\n", distance);

    if (distance < 300 && !isDoorOpen) {
      int command = 1;  // Buka pintu
      xQueueSend(taskQueue, &command, 0);
    } else if (distance >= 300 && isDoorOpen) {
      int command = 0;  // Tutup pintu
      xQueueSend(taskQueue, &command, 0);
    }
  }
}

// Interrupt untuk menghentikan pengukuran sensor
void IRsensorInterrupt() {
  if (ignoreSensor) {
    Serial.println("IR sensor paused.");
    xTimerStop(sensorTimer, 0); // Hentikan software timer
    delay(5000);                // Simulasi jeda 5 detik

  } else if (!ignoreSensor){
    ignoreSensor = false;
    xTimerStart(sensorTimer, 0); // Mulai ulang software timer
    Serial.println("IR sensor resumed.");
  }
}

// Mengecek input dari button fisik
void checkPhysicalButtonTask(void* parameter) {
  while (1) {
    if (digitalRead(BUTTON_PIN) == LOW) {
      int command = isDoorOpen ? 0 : 1;  // Buka/tutup pintu sesuai kondisi pintu sekarang
      xQueueSend(taskQueue, &command, 0);
      delay(300);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
