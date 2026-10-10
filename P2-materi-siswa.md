# Materi Siswa — ESP32, Pin, Sensor, dan Pembacaan Data

**Proyek:** sistem penyiraman otomatis berbasis ESP32 · **Pertemuan 2**

Halo! Pada pertemuan ini kamu akan mengenal ESP32, sensor kelembapan, dan relay/driver. Setelah menghubungkan sensor, kamu juga akan **membaca nilainya** di komputer. Materi ini bisa kamu baca dan pelajari sendiri, lalu kerjakan bagian praktik dan tabel pengamatannya.

---

## Setelah mempelajari ini, kamu bisa

- Menjelaskan mikrokontroler dan alur masukan → proses → keluaran.
- Menunjukkan pin daya, GND, GPIO, dan pin analog pada ESP32.
- Menghubungkan sensor ke ESP32 sesuai spesifikasi.
- Menjelaskan fungsi sensor dan relay/driver.
- Menjelaskan ADC dan membaca nilai sensor di Serial Monitor.
- Mencatat nilai sensor pada beberapa sampel tanah secara konsisten.
- Menyebutkan aturan keselamatan sebelum dan saat rangkaian diberi daya.

---

## Istilah penting

| Istilah | Arti singkat |
|---|---|
| **Mikrokontroler** | Komputer kecil dalam satu chip untuk mengendalikan perangkat. |
| **GPIO** | Pin yang bisa dipakai sebagai masukan atau keluaran. |
| **GND** | Ground, acuan tegangan/rangkaian. |
| **Tegangan logika** | Tegangan sinyal yang dipakai pin (ESP32 = 3,3 V). |
| **Sensor** | Alat yang mengubah kondisi (mis. kelembapan) menjadi sinyal listrik. |
| **Relay/driver** | Perantara agar sinyal kendali bisa mengoperasikan beban. |
| **Tegangan analog** | Tegangan yang berubah halus, seperti raksa termometer. |
| **ADC** | Bagian ESP32 yang mengubah tegangan menjadi angka. |
| **Serial Monitor** | Layar di Arduino IDE untuk melihat angka dari ESP32. |
| **Baud rate** | Kecepatan kirim data; program dan Serial Monitor harus sama. |
| **Nilai mentah** | Angka ADC apa adanya, sebelum diolah jadi persen. |

---

## Materi

### 1. Mikrokontroler dan alur sistem

Mikrokontroler adalah komputer kecil dalam satu chip yang menjalankan program untuk mengendalikan perangkat. ESP32 punya mikrokontroler, pin masukan/keluaran, dan antarmuka catu daya.

```mermaid
flowchart LR
    T[Kondisi tanah] --> S[Sensor kelembapan<br/>Masukan]
    S --> E[ESP32<br/>Pemroses]
    E -->|Sinyal kendali| R[Relay / driver]
    R --> P[Pompa<br/>Beban / keluaran]
```

Sensor memberi **informasi**, ESP32 **memproses**, relay/driver membantu sinyal kendali mengoperasikan **beban**. Jalur sinyal (informasi) dan jalur daya (energi) berbeda.

### 2. Input, proses, output, dan GPIO

- **Input/masukan:** data yang diterima, misalnya sinyal sensor.
- **Proses:** keputusan program di ESP32.
- **Output/keluaran:** sinyal kendali, misalnya mengaktifkan relay.
- **GPIO:** pin yang bisa jadi masukan atau keluaran.
- **GND:** ground/acuan tegangan.
- **VCC/3V3/5V:** sambungan catu daya; pin 5V bukan pin sinyal GPIO.

Sebagian pin punya fungsi khusus. Pilih pin sesuai pinout board yang kamu pakai, bukan meniru contoh board lain.

### 3. Tegangan logika ESP32

GPIO ESP32 bekerja pada **3,3 V** dan tidak tahan menerima 5 V langsung. 5 V ke GPIO bisa merusak board.

Sebelum menghubungkan sensor: cek tegangan catu sensor dan batas sinyal keluarannya. Sinyal ke ESP32 **tidak boleh melebihi 3,3 V**. Kalau belum yakin, **jangan sambung atau beri daya** — minta guru memeriksa.

### 4. Sensor kelembapan kapasitif

Sensor mendeteksi perubahan kadar air dan mengeluarkan sinyal listrik. Label yang biasa ada:

- **VCC** = catu positif sesuai spesifikasi.
- **GND** = ground.
- **OUT/AOUT** = keluaran sinyal, ke pin masukan ESP32.

Jangan merendam sensor kecuali manual menyatakan aman.

### 5. Relay, driver, dan beban

Relay adalah saklar yang digerakkan sinyal listrik. Driver transistor/MOSFET pilihan lain untuk beban DC. Pompa butuh arus lebih besar dari kemampuan pin.

- **Jangan sambungkan pompa langsung ke GPIO.**
- Relay bisa aktif-HIGH atau aktif-LOW; periksa label/datasheet.
- Sisi kendali (IN, VCC, GND) dan sisi kontak beban (COM, NO, NC) berbeda fungsi.

### 6. Membaca data: dari tegangan ke angka (ADC)

Sensor mengeluarkan **tegangan analog** yang berubah mengikuti kondisi tanah. **ADC** mengubah tegangan itu menjadi **angka** yang bisa diproses.

```mermaid
flowchart LR
    T[Tanah kering/lembap] --> S[Sensor<br/>tegangan analog]
    S --> A[ADC<br/>jadikan angka]
    A --> M[Serial Monitor<br/>angka terlihat]
```

### 7. Serial Monitor

**Serial Monitor** menampilkan angka yang dikirim ESP32 lewat USB. **Baud rate** program dan Serial Monitor harus sama (contoh `115200`).

```text
Nilai sensor: 2814
Nilai sensor: 2809
Nilai sensor: 2811
```

Angka boleh sedikit berbeda — itu wajar.

### 8. Pin analog dan pin masukan

- **GPIO 34 dan 35** pada ESP32 klasik adalah **pin masukan saja** (bisa baca analog, tidak bisa jadi keluaran).
- GPIO 32/33 juga bisa baca analog di banyak board; cocokkan dengan pinout kamu.
- Sinyal ke pin analog tidak boleh melebihi 3,3 V.

### 9. Angka ADC bukan persen

Angka `2814` atau `1045` **bukan** "28%" atau "10%". Itu **nilai mentah** ADC. Jadi persen perlu **kalibrasi** (dipelajari nanti).

Contoh (bergantung sensor dan board):

| Sampel tanah | Contoh nilai ADC |
|---|---|
| Kering | 2814 |
| Lembap | 1902 |
| Basah | 1045 |

> ⚠️ Arah perubahan bisa berbeda antarsensor — amati dan catat, jangan menebak.

### 10. Kenapa angka bisa berubah?

Selain kadar air, nilai dipengaruhi jenis tanah, kedalaman, posisi sensor, dan kestabilan catu daya. Karena itu jaga **kedalaman dan posisi sensor tetap sama** saat membandingkan sampel.

> 💡 **Coba cek:** Sebutkan dua hal (selain kadar air) yang bisa mengubah nilai sensor.

<details>
<summary>Lihat jawaban</summary>

Jenis tanah, kedalaman, posisi sensor, atau kestabilan catu daya (cukup dua).
</details>

> 💡 **Coba cek:** Apa yang terjadi kalau baud rate program `115200` tapi Serial Monitor `9600`?

<details>
<summary>Lihat jawaban</summary>

Data tampil kacau atau tidak terbaca karena kecepatan kirim di kedua sisi berbeda.
</details>

---

## Langkah kerja praktik

**Ingat:** rangkaian akan diberi daya, jadi jangan menyentuh kabel atau sambungan saat menyala.

1. **Siapkan alat** — ESP32 + sensor, kabel USB, komputer dengan Arduino IDE, dan tiga sampel tanah (kering, lembap, basah).
2. **Sambungkan sensor** ke ESP32 sesuai diagram guru (daya terlepas): VCC → catu, GND → GND, OUT → pin analog. Minta guru memeriksa sebelum memberi daya.
3. **Buka sketch** pembacaan sensor dari guru (kamu tidak menulis program hari ini).

   ```cpp
   // Sketch pembacaan sensor kelembapan (disiapkan guru).
   const int sensorPin = 34;   // pin analog sesuai diagram guru

   void setup() {
     Serial.begin(115200);     // baud rate = 115200
   }

   void loop() {
     int nilaiSensor = analogRead(sensorPin); // baca tegangan, jadikan angka
     Serial.print("Nilai sensor: ");
     Serial.println(nilaiSensor);
     delay(500);               // jeda 0,5 detik
   }
   ```

4. **Unggah (upload)** sketch ke ESP32.
5. **Buka Serial Monitor** dan pastikan baud rate-nya `115200`. Angka akan muncul berulang.
6. **Amati sampel** — tancapkan sensor pada sampel kering, catat beberapa angka. Ulangi untuk lembap dan basah. **Jaga kedalaman dan posisi sensor tetap sama** di tiap sampel.
7. **Catat hasilnya** pada tabel pengamatan di bawah.

> 🛑 **Keselamatan:** lepaskan daya saat memasang/mengubah kabel. Jangan menyentuh rangkaian saat daya aktif. Jauhkan air dari ESP32 dan sambungan.

---

## Tabel pengamatan

**Nama:** ____________________  **Kelompok:** __________  **Tanggal:** __________

Jaga kedalaman dan posisi sensor tetap sama. Catat tiga pembacaan, lalu isi rata-ratanya (jumlah ketiga nilai dibagi 3).

| Sampel tanah | Kedalaman/posisi | Nilai 1 | Nilai 2 | Nilai 3 | Rata-rata (jumlah ÷ 3) | Catatan |
|---|---|---|---|---|---|---|
| Kering | | | | | | |
| Lembap | | | | | | |
| Basah | | | | | | |
| Tanah di pot/area uji (opsional) | | | | | | |

Jawab singkat:

1. Sampel mana yang memberi nilai paling berbeda? ______________
2. Apakah nilai naik atau turun saat tanah makin basah? ______________
3. Apakah angka-angka itu sudah merupakan persen kelembapan? Mengapa? ______________

---

## Pertanyaan refleksi

1. Apa yang dilakukan ESP32 ketika kondisi tanah berubah?
2. Mengapa pompa tidak boleh dihubungkan langsung ke GPIO?
3. Dengan kata-katamu sendiri, apa tugas **ADC**?
4. Kenapa angka `1902` belum tentu berarti "19% kelembapan"?
5. Apa yang kamu lakukan supaya perbandingan antar sampel itu adil (konsisten)?
6. Sebutkan satu tindakan aman sebelum mengubah sambungan, dan satu saat rangkaian diberi daya.

---

## Rangkuman

- Sensor mengubah kondisi tanah menjadi **tegangan analog**; **ADC** mengubahnya menjadi **angka**.
- **Serial Monitor** menampilkan angka; **baud rate** program dan Serial Monitor harus sama.
- Angka yang tampil adalah **nilai mentah**, **bukan persen**.
- Pompa dioperasikan lewat **relay/driver**, bukan langsung ke GPIO.
- Jaga **posisi/kedalaman sensor** tetap konsisten, dan utamakan keselamatan.

---

## Catatan keselamatan

1. Lepaskan sumber daya sebelum memasang atau mengubah kabel.
2. Jangan pernah memasukkan 5 V ke GPIO; batas sinyal GPIO adalah 3,3 V.
3. Jangan hubungkan pompa, motor, atau beban berarus besar langsung ke GPIO.
4. Jangan menyentuh rangkaian, kabel, atau sambungan saat diberi daya.
5. Jauhkan air dari ESP32, sambungan, dan catu daya. Jangan merendam sensor kecuali manual menyatakan aman.
6. Beri tahu guru jika ada kabel terkelupas, komponen panas, bau, atau percikan.
