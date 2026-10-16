# Silabus Pembelajaran 24 Pertemuan: Sistem Penyiraman Otomatis Berbasis Energi Surya
**Target Siswa:** SMP (Sekolah Menengah Pertama) | **Durasi:** 90 Menit / Pertemuan | **Platform:** Arduino IDE (C++)

---

## 1. Electronic + Testing (10% | 2 Pertemuan)
*   **Pertemuan 1: Pre-Test & Pengantar Proyek** 
    *   Pelaksanaan Pre-Test (Penilaian Diri) untuk memetakan pemahaman dasar siswa.
    *   Pengenalan skema *off-grid*: Panel Surya 20Wp, SCC 10A, dan Baterai VRLA 12V 7Ah[span_0](start_span)[span_0](end_span).
*   **Pertemuan 2: Pengenalan Mikrokontroler & Uji Sensor**
    *   Pengenalan ESP32 DevKit V1 dan Modul Relay[span_1](start_span)[span_1](end_span).
    *   Uji coba Sensor Kelembapan Kapasitif v1.2 pada kondisi kering (udara) dan basah (air)[span_2](start_span)[span_2](end_span).

## 2. Mechanical Design 3D (5% | 1 Pertemuan)
*   **Pertemuan 3: Desain Enclosure Box**
    *   Menggunakan Tinkercad untuk mendesain *Box Enclosure IP65* tahan cuaca[span_3](start_span)[span_3](end_span).
    *   Membuat lubang presisi untuk kabel USB dan kabel sensor.

## 3. Programming Part (20% | 5 Pertemuan)
*   **Pertemuan 4: Sintaks C++ Dasar & Output Digital**
    *   Struktur `setup()` dan `loop()`, inisialisasi Serial Monitor 115200 bps[span_4](start_span)[span_4](end_span).
    *   Memprogram GPIO 27 untuk menyalakan Buzzer[span_5](start_span)[span_5](end_span).
*   **Pertemuan 5: Input Analog**
    *   Membaca tegangan analog dari GPIO 34 dan GPIO 35 (Sensor 1 & 2)[span_6](start_span)[span_6](end_span).
*   **Pertemuan 6: Matematika dalam C++**
    *   Konversi *raw* ADC ke persentase (0-100%) dan menghitung rata-rata (`avgMoisture`)[span_7](start_span)[span_7](end_span).
*   **Pertemuan 7: Logika Kontrol Relay**
    *   Menerapkan *If-Else*: Jika `avgMoisture` < 60%, aktifkan GPIO 26 (Relay ON)[span_8](start_span)[span_8](end_span).
*   **Pertemuan 8: Terminasi Penyiraman**
    *   Logika stop: Jika `avgMoisture` >= 85%, Relay OFF dan Buzzer bunyi 3x[span_9](start_span)[span_9](end_span).

## 4. Assembly Programming (15% | 4 Pertemuan)
*   **Pertemuan 9: Inisialisasi Sistem Dasar**
    *   Membuat *State Machine* awal: Buzzer bunyi 2x saat ESP32 menyala[span_10](start_span)[span_10](end_span).
*   **Pertemuan 10: Algoritma Fase ON**
    *   Mengatur fungsi `delay()` untuk `pumpOnTime` selama 5000 ms (5 detik)[span_11](start_span)[span_11](end_span).
*   **Pertemuan 11: Algoritma Fase SOAKING**
    *   Mengatur `delay()` untuk `soakTime` selama 55000 ms (55 detik) untuk peresapan[span_12](start_span)[span_12](end_span).
*   **Pertemuan 12: Penggabungan & Simulasi Kode**
    *   Menggabungkan seluruh baris kode menjadi satu siklus *pulsing* penyiraman utuh[span_13](start_span)[span_13](end_span).

## 5. Assembly Mekanik, Elektrik, Programming (30% | 7 Pertemuan)
*   **Pertemuan 13: Keamanan Hardware (Dioda Proteksi)**
    *   Menyolder *Flyback Diode* 1N4007 paralel-terbalik di motor Pompa DC untuk mencegah lonjakan tegangan (*back-EMF*)[span_14](start_span)[span_14](end_span).
*   **Pertemuan 14: Perakitan Tenaga Surya**
    *   Menghubungkan Baterai 7Ah dan Panel Surya ke SCC dengan aman[span_15](start_span)[span_15](end_span).
*   **Pertemuan 15: Wiring Jalur Daya**
    *   Menarik kabel 12V dari SCC ke Relay/Pompa, dan kabel USB 5V ke ESP32[span_16](start_span)[span_16](end_span).
*   **Pertemuan 16: Perakitan Komponen ke Box**
    *   Memasukkan ESP32 dan Relay ke dalam *Box Enclosure* 3D hasil cetak.
*   **Pertemuan 17: Upload Kode Final**
    *   Mengunggah program final ke ESP32 yang sudah dirangkai dengan *hardware*.
*   **Pertemuan 18: Instalasi Pipa Air**
    *   Memasang selang PE 5/16" dari Pompa Mini DC 12V ke Tandon Galon 19 Liter[span_17](start_span)[span_17](end_span).
*   **Pertemuan 19: Setup di Lahan Pot**
    *   Memposisikan 2 sensor dan ujung selang *drip* di dua pot tanaman (lahan 80x40 cm)[span_18](start_span)[span_18](end_span).

## 6. Debugging & Evaluasi (20% | 5 Pertemuan)
*   **Pertemuan 20: Debugging Catu Daya**
    *   Memastikan tegangan USB SCC stabil di 5.0V untuk mencegah ESP32 *hang*[span_19](start_span)[span_19](end_span).
*   **Pertemuan 21: Kalibrasi Akurasi Sensor**
    *   Menyesuaikan nilai konversi ADC berdasarkan pembacaan tanah asli di pot[span_20](start_span)[span_20](end_span).
*   **Pertemuan 22: Pengujian Stabilitas (Hardware Safety)**
    *   Menguji on-off pompa secara ekstrem untuk memastikan keberhasilan *flyback diode* 1N4007[span_21](start_span)[span_21](end_span).
*   **Pertemuan 23: Evaluasi Siklus Pulsing**
    *   Menguji fungsionalitas siklus menyala 5 detik dan jeda 55 detik pada tanah yang < 60%[span_22](start_span)[span_22](end_span).
*   **Pertemuan 24: Post-Test, Presentasi & Tanya Jawab**
    *   Mengamati berhentinya penyiraman secara otomatis pada kelembapan >= 85%[span_23](start_span)[span_23](end_span).
    *   Siswa mempresentasikan hasil rakitan, cara kerja logika, dan menjawab *Post-Test* lisan/tulis dari pengajar.

---

## Lampiran 1: Instrumen Pre-Test (Pertemuan 1)
*Format: Survei Penilaian Diri (Paham / Sedikit Paham / Kurang Tahu / Tidak Tahu)*

1. Cara kerja Panel Surya dalam mengubah cahaya matahari menjadi listrik[span_24](start_span)[span_24](end_span).
2. Cara menghubungkan kutub positif dan negatif baterai ke alat elektronik agar aman[span_25](start_span)[span_25](end_span).
3. Fungsi dari Mikrokontroler (seperti ESP32) sebagai "otak" sebuah mesin otomatis[span_26](start_span)[span_26](end_span).
4. Cara kerja logika dasar komputer seperti "JIKA (kondisi), MAKA (lakukan sesuatu)[span_27](start_span)"[span_27](end_span).
5. Cara membuat rumus rata-rata dari dua buah nilai/angka menggunakan komputer[span_28](start_span)[span_28](end_span).

## Lampiran 2: Panduan Post-Test & Tanya Jawab (Pertemuan 24)
*Format: Pertanyaan Lisan selama Presentasi Kelompok*

1. **Pemahaman Hardware:** Mengapa kita wajib menggunakan komponen *diode* pada mesin pompa air yang kita pasang?[span_29](start_span)[span_29](end_span)
2. **Pemahaman Coding:** Di dalam program Arduino IDE kalian, baris kode apa yang mengatur agar air tidak menyiram terus-menerus dan punya waktu tunggu 55 detik?[span_30](start_span)[span_30](end_span)
3. **Pemahaman Logika Sistem:** Coba jelaskan, kapan tepatnya sistem ini memutuskan untuk mulai menyalakan pompa, dan kapan sistem berhenti menyiram?[span_31](start_span)[span_31](end_span)
