
# Smart Garage Door

Sistem IoT yang dapat membuka dan menutup pintu garasi berdasarkan jarak kendaraan terhadap sensor IR.

## Introduction to the problem and the solution
Dalam era digital yang semakin maju, kebutuhan akan sistem otomasi rumah yang efisien dan aman semakin meningkat. Salah satu area yang memerlukan perhatian khusus adalah sistem pintu garasi. Sistem pintu garasi konvensional seringkali memiliki keterbatasan dalam hal kemudahan penggunaan, keamanan, dan integrasi dengan teknologi modern. Pengguna menghadapi kesulitan dalam mengontrol pintu garasi dari jarak jauh, memantau statusnya, dan mengintegrasikannya dengan sistem rumah pintar lainnya. Selain itu, sistem yang ada saat ini kurang responsif terhadap kehadiran kendaraan dan tidak menyediakan umpan balik visual yang memadai tentang status pintu. Oleh karena itu, diperlukan solusi yang dapat mengatasi keterbatasan ini dan meningkatkan pengalaman pengguna dalam mengelola akses garasi mereka

Untuk mengatasi masalah tersebut, kami mengusulkan pengembangan sistem Smart Garage Door berbasis IoT menggunakan platform ESP32 dan Blynk. Solusi ini akan mengintegrasikan berbagai komponen hardware dan software untuk menciptakan sistem pintu garasi yang cerdas, responsif, dan mudah digunakan. Sistem ini akan memanfaatkan sensor inframerah untuk mendeteksi kehadiran kendaraan, servo motor untuk menggerakkan pintu, dan LED indikator untuk memberikan umpan balik visual. Pengguna akan dapat mengontrol pintu garasi melalui aplikasi Blynk di smartphone mereka, memungkinkan akses dan pemantauan jarak jauh. Sistem juga akan dilengkapi dengan tombol fisik untuk kontrol manual, memberikan fleksibilitas tambahan. Penggunaan teknik multitasking dan manajemen sumber daya yang efisien akan memastikan responsivitas dan keandalan sistem.



## Hardware design and implementation details
Pembuatan Smart Garage Door dimulai dengan merancang prototipe menggunakan Wokwi, hal ini dilakukan untuk mempermudah saat merakit rangkaian asli yang menggunakan komponen asli agar tidak terjadi kesalahan pada rangkaian dan kesalahan integrasi antar komponen yang digunakan. 


Proyek Smart Garage Door ini menggunakan beberapa komponen hardware yang digunakan untuk merangkai skema alat dan fungsinya dalam rangkaian yaitu:

1. 2 buah breadboards
Breadboards digunakan untuk menghubungkan seluruh komponen hardware yang akan digunakan.

2. 1 buah ESP32
ESP32 merupakan microcontroller yang akan digunakan untuk mengatur keseluruhan sistem IoT ini bekerja.

3. 1 buah Servo
Servo digunakan sebagai komponen yang disimulasikan sebagai pintu garasi, dimana servo akan bergerak seakan-akan menutup atau membuka pintu garasi.

4. 2 buah LED
2 buah LED akan digunakan sebagai indikator fisik yang menyatakan kondisi pintu garasi, LED merah akan menyala jika pintu garasi tertutup dan LED hijau akan menyala jika pintu garasi terbuka.

5. 1 buah Button
Button digunakan sebagai alat untuk membuka pintu garasi secara manual. 

6. 1 buah sensor Infrared
Sensor infrared digunakan sebagai sensor untuk mendeteksi jarak kendaraan terhadap pintu garasi. 



## Software implementation details

![Flowchart](https://hackmd.io/_uploads/Syx57k8NJl.png)
Berdasarkan flowchart tersebut, diketahui bahwa Smart Garage Door akan menerima data jarak dari sensor Infrared yang dikirim ke ESP32, lalu ESP32 akan menentukan apakah pintu garasi akan dibuka atau ditutup berdasarkan kondisi pintu garasi dan data jarak yang berhasil didapat. 

Selain itu, Smart Garage Door ini juga menggunakan Blynk untuk memberikan feedback ke user mengenai hasil dari Smart Garage Door. Blynk memiliki sebuah power button dan LED yang akan menyatakan hasil dari Smart Garage Door. Power button ini dapat digunakan oleh user untuk membuka dan menutup pintu garasi secara jarak jauh. Dan LED digunakan sebagai indikator apakah pintu garasi sedang terbuka atau tidak. 



## Test results and performance evaluation


![Rangkaian ketika terdapat objek ](https://hackmd.io/_uploads/ByDJVJLEyx.jpg)

Berdasarkan hasil diatas, dapat dilihat bahwa LED hijau pada rangkaian fisik dan LED pada Blynk menyala ketika terdapat objek yang berjarak dekat dengan sensor Infrared, dan juga Servo bergerak sebesar 90°. Hal ini menunjukkan bahwa ESP32 berhasil mendeteksi jarak yang didapat dari sensor Infrared, dan dikarenakan jarak objek terlalu dekat dengan sensor sehingga ESP32 akan menyalakan LED hijau di rangkaian fisik dan menyalakan LED pada Blynk.



![Rangkaian ketika menutup pintu garasi secara manual
](https://hackmd.io/_uploads/BJD141I4Je.jpg)

Setelah ESP32 berhasil menyalakan LED dan menggerakan Servo yang menandakan bahwa pintu garasi terbuka ketika terdapat objek yang dekat dengan sensor, pintu garasi akan ditutup secara manual menggunakan button pada rangkaian fisik. Sehingga hasilnya seperti dibawah:


![Rangkaian ketika pintu garasi tertutup](https://hackmd.io/_uploads/Bk_JV1LV1e.jpg)


Dapat dilihat bahwa setelah button ditekan, LED merah pada rangkaian fisik menyala dan LED pada Blynk tidak menyala. Selain itu juga Servo bergerak kembali ke posisi semula. Hal ini menunjukkan bahwa ESP32 berhasil menutup pintu garasi secara manual.



Hasil pada rangkaian fisik Smart Garage Door sudah sesuai seperti yang diharapkan dan yang digambarkan pada flowchart, hanya saja terdapat sebuah kekurangan dari Smart Garage Door yang sudah dibuat. Kekurangan ini yaitu Smart Garage Door tidak bisa menutup pintu garasi kembali ketika pintu garasi sudah terbuka sebelumnya, pintu garasi hanya bisa ditutup secara manual menggunakan button pada rangkaian fisik atau button pada Blynk. 
Kekurangan ini bisa disebabkan oleh beberapa faktor, salah satunya adalah karena sensor Infrared selalu mendeteksi adanya objek yang berada di dekatnya sehingga pintu garasi akan terus terbuka. Hal ini bisa terjadi karena rangkaian fisik tempat sensor Infrared dipasang berada dekat dengan objek - objek lainnya. 


## Conclusion and future work

Dengan keberhasilan proyek ini, diharapkan dapat membuka wawasan kita lebih luas mengenai dunia Internet of Things (IoT). Proyek ini tidak hanya memberikan pemahaman teknis, tetapi juga memperkenalkan kita pada penerapan teknologi IoT dalam kehidupan sehari-hari. Melalui proyek ini, kita dapat mempelajari bagaimana sistem pintar seperti Smart Garage System dirancang untuk memberikan solusi otomatisasi yang praktis dan inovatif.

Proyek ini dirancang untuk membantu pengguna mengelola pintu garasi rumah mereka dengan lebih mudah dan efisien. Dengan fitur seperti deteksi kendaraan otomatis, notifikasi real-time, dan pengoperasian jarak jauh melalui aplikasi Blynk, sistem ini mampu menjawab tantangan sehari-hari terkait keamanan dan kenyamanan. Pengguna tidak perlu khawatir lupa menutup pintu garasi atau mengalami kesulitan dalam mengelolanya, karena semua fungsi ini dapat dilakukan secara otomatis dan praktis.

Selain itu, proyek ini juga menjadi bukti nyata bagaimana teknologi dapat meningkatkan kualitas hidup manusia. Dengan mengintegrasikan perangkat keras dan perangkat lunak, proyek ini memberikan pengalaman baru dalam menggunakan teknologi pintar. Tidak hanya itu, proyek ini memberikan kesempatan untuk memahami konsep-konsep penting seperti sensor, automasi, dan pengelolaan data, yang merupakan inti dari pengembangan sistem IoT.

Kesimpulannya, keberhasilan proyek ini tidak hanya memberikan manfaat praktis bagi pengguna, tetapi juga menjadi pembelajaran penting bagi kita sebagai mahasiswa. Dengan mempelajari dan menerapkan teknologi IoT, kita dapat mengembangkan ide-ide inovatif lainnya di masa depan. Smart Garage System menjadi langkah awal untuk menunjukkan bagaimana teknologi pintar dapat mengubah cara kita menjalani kehidupan sehari-hari menjadi lebih mudah, aman, dan efisien.








