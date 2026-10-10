# Silabus 12 Pertemuan: Sistem Penyiraman Otomatis Berbasis Energi Surya

**Target siswa:** SMA pemula (tidak harus pernah belajar Arduino atau C++)  
**Durasi:** 90 menit per pertemuan  
**Platform:** Arduino IDE (C++) dengan ESP32 DevKit V1

## Tujuan umum

Pada akhir pembelajaran, siswa dapat menjelaskan alur kerja sistem, membaca dan mengalibrasi sensor kelembapan, membuat program kendali sederhana, serta menguji prototipe dengan aman.

## Alokasi tahap

| Tahap | Pertemuan | Porsi |
|---|---:|---:|
| Pengantar proyek dan keselamatan | 1 | 5% |
| Elektronika dan pembacaan sensor | 2 | 5% |
| Desain skematik dan PCB | 3 | 5% |
| Dasar dan integrasi pemrograman | 4–5 (2 pertemuan) | 30% |
| Perencanaan integrasi dan wiring | 6 | 5% |
| Desain mekanik | 7–8 (2 pertemuan) | 10% |
| Perakitan dan integrasi sistem | 9–10 (2 pertemuan) | 20% |
| Debugging dan evaluasi | 11–12 (2 pertemuan) | 20% |
| **Total** | **12 pertemuan** | **100%** |

## Keselamatan dan persiapan kelas

- Guru memeriksa polaritas dan rangkaian sebelum daya disambungkan. Lepaskan sumber daya sebelum mengubah kabel.
- Pompa tidak boleh dihubungkan langsung ke GPIO ESP32. GPIO hanya memberi sinyal kendali; pompa memakai driver/relay dan sumber daya yang sesuai.
- Pastikan tegangan sinyal sensor yang masuk ke ESP32 tidak melebihi 3,3 V. Periksa spesifikasi modul dan pinout board.
- Baterai, panel, solder, dan pompa hanya dirakit atau diuji dengan pengawasan guru serta mengikuti manual komponen. Sediakan sekering dan kabel yang sesuai arus bila diperlukan.
- Jauhkan sambungan listrik dari air. Gunakan wadah penampung saat menguji pompa dan jangan menjalankan pompa tanpa air jika produsennya melarang.
- Karena waktu hanya 12 pertemuan, guru disarankan menyiapkan diagram wiring, komponen yang sudah diperiksa, dan—bila fasilitas terbatas—rangkaian daya yang telah dirakit. Siswa tetap melakukan pemeriksaan, pengukuran, dan pengujian bertahap.

---

## Pertemuan 1: Pengantar proyek, pre-test, dan keselamatan
- **Materi:** tujuan proyek dan diagram alur energi/sinyal: panel surya → SCC → baterai dan beban; sensor → ESP32 → relay/driver → pompa. Contoh komponen: panel 20 Wp, SCC 10 A, baterai VRLA 12 V 7 Ah. Kesesuaian akhir harus diverifikasi terhadap beban dan manual produsen.
- **Materi inti:** panel mengubah cahaya menjadi listrik DC; SCC mengatur pengisian baterai; baterai menyimpan energi; ESP32 membaca sensor dan memberi sinyal kendali; pompa memindahkan air. Bedakan **jalur energi** (baterai ke beban) dari **jalur informasi** (sensor ke ESP32). Angka Wp adalah daya puncak panel pada kondisi uji tertentu, bukan jaminan daya yang selalu tersedia.
- **Kegiatan:** pre-test, mengenali komponen, membuat diagram blok, dan membahas aturan keselamatan.
- **Hasil belajar:** siswa dapat menjelaskan fungsi komponen utama dan menyebutkan pemeriksaan keselamatan sebelum rangkaian diberi daya.
- **Bukti belajar:** diagram blok berlabel dan lembar pre-test.

## Pertemuan 2: ESP32, pin, sensor, dan pembacaan data
- **Materi:** mikrokontroler, masukan/keluaran, GPIO, sensor kapasitif, relay/driver, pembacaan analog, dan Serial Monitor.
- **Materi inti:** GPIO membaca sinyal atau memberi sinyal kendali; ESP32 bekerja pada logika 3,3 V, jangan berikan 5 V ke GPIO. Sensor mengubah kondisi tanah menjadi sinyal listrik; ADC mengubah tegangan sensor menjadi angka digital yang dibaca lewat Serial Monitor. Angka tersebut belum merupakan persen kelembapan. Relay/driver memungkinkan sinyal kendali mengoperasikan beban yang memerlukan jalur daya terpisah. GPIO 34/35 pada ESP32 klasik adalah pin masukan saja; verifikasi pinout board yang digunakan.
- **Kegiatan:** mengenali ESP32 DevKit V1 dan diagram pin; menghubungkan sensor sesuai spesifikasi modul; mengunggah sketch pembacaan yang disiapkan guru; mencatat beberapa nilai pada sampel tanah berbeda dengan posisi sensor yang konsisten.
- **Hasil belajar:** siswa dapat menunjukkan pin daya, ground, dan sinyal, menjelaskan fungsi sensor serta relay, membaca dan mencatat nilai sensor, dan menghubungkan perubahan nilai dengan kondisi sampel.
- **Bukti belajar:** gambar sambungan yang diperiksa guru dan tabel pengamatan sensor.

## Pertemuan 3: Desain skematik dan PCB dengan EasyEDA
- **Materi:** skema (schematic), simbol komponen, net/net label, konversi skema ke PCB, penempatan komponen, routing, dan DRC di EasyEDA.
- **Materi inti:** skema menggambarkan hubungan listrik antarkomponen memakai simbol, bukan bentuk fisik. Net label (GND, VCC, sinyal) menghubungkan pin tanpa menarik kawat panjang. Dari skema, EasyEDA membuat PCB dengan footprint; siswa menempatkan komponen, melakukan routing jalur, lalu menjalankan DRC agar tidak ada jalur tumpang-tindih atau sambungan terputus. Fabrikasi dan penyolderan dilakukan terpisah dengan pengawasan guru.
- **Kegiatan:** mereproduksi skema acuan (sensor → ESP32 → relay/driver) di EasyEDA; mengubahnya menjadi PCB; menempatkan komponen dan melakukan routing; menjalankan DRC.
- **Hasil belajar:** siswa dapat membuat skema sederhana, mengubahnya menjadi layout PCB, dan menyebutkan pemeriksaan DRC sebelum desain dianggap selesai.
- **Bukti belajar:** skema dan layout PCB yang lolos DRC.

## Pertemuan 4: Dasar C++ dan membaca sensor
- **Materi:** `setup()`, `loop()`, komentar, variabel, `pinMode()`, `digitalWrite()`, dan Serial Monitor 115200 bps.
- **Materi inti:** `setup()` berjalan sekali saat board mulai, sedangkan `loop()` berulang terus. Variabel menyimpan nilai; `pinMode()` menentukan fungsi pin; `digitalWrite()` mengatur keluaran digital HIGH/LOW. Baud rate Serial Monitor dan program harus sama. Siswa membaca contoh sensor sebagai kode yang sudah disediakan sebelum diminta mengubah bagian-bagiannya.
- **Kegiatan:** mulai dari template program yang disediakan guru. Ubah program buzzer pada GPIO 27, lalu telusuri contoh untuk membaca sensor di GPIO 34/35 dan menampilkan nilainya. Periksa apakah buzzer aktif-HIGH atau aktif-LOW.
- **Hasil belajar:** siswa dapat mengunggah program, mengubah jumlah bunyi/jeda, dan menemukan bagian kode yang membaca sensor.
- **Bukti belajar:** program contoh yang berjalan dan catatan satu nilai sensor.

## Pertemuan 5: Kalibrasi dan integrasi logika penyiraman
- **Materi:** nilai ADC, persentase, rata-rata, `if`/`else`, status sistem, dan waktu siklus.
- **Materi inti:** kalibrasi menetapkan nilai acuan kering dan lembap untuk sensor yang benar-benar dipakai. Nilai persentase adalah skala relatif hasil kalibrasi, bukan pengukuran ilmiah universal. Rata-rata dua sensor meringkas data tetapi dapat menutupi satu pot yang sangat kering. Kondisi mulai `< 60%` dan berhenti `>= 85%` membentuk dua ambang; variabel status mengingat apakah sistem sedang menyiram.
- **Kegiatan:** gunakan nilai acuan `rawDry` pada tanah kering dan `rawWet` pada tanah lembap. Rumus awal: `moisture = (raw - rawDry) * 100.0 / (rawWet - rawDry)`, lalu batasi ke 0–100 dan hindari pembagian dengan nol. Dengan template guru, uji mulai `< 60%`, pulsa pompa 5 detik (`pumpOnTime = 5000`), jeda 55 detik (`soakTime = 55000`), baca ulang, lalu berhenti ketika `>= 85%`. Simulasikan dahulu lewat Serial Monitor/LED/relay tanpa pompa.
- **Hasil belajar:** siswa dapat menelusuri satu siklus dan menjelaskan kondisi mulai, jeda, pembacaan ulang, serta berhenti.
- **Catatan:** nilai sensor bisa naik atau turun saat makin basah; gunakan hasil kalibrasi, bukan angka universal. Dua ambang memerlukan status sistem. Rata-rata dua sensor dapat menyembunyikan pot yang kering; tentukan apakah keputusan memakai rata-rata, sensor terendah, atau kendali terpisah. `delay()` cukup untuk prototipe sederhana tetapi menghentikan tugas lain selama menunggu; `millis()` dapat menjadi pengembangan lanjutan.
- **Catatan pembelajaran:** dua sesi pemrograman cukup padat untuk pemula. Gunakan kode kerangka yang sudah diuji, fokuskan latihan pada membaca dan mengubah bagian kode, dan siapkan waktu tambahan bila siswa benar-benar baru mengenal komputer atau pemrograman.

## Pertemuan 6: Perencanaan integrasi dan wiring
- **Materi:** fungsi panel, SCC, baterai, sekering, relay/driver; pemisahan jalur sinyal dan daya; alur air dan daftar komponen.
- **Materi inti:** baca simbol positif/negatif, terminal baterai/panel/beban, kontak relay, dan rating arus/tegangan pada label. Pompa adalah beban motor yang dapat menarik arus awal lebih besar daripada arus saat berputar. Dioda flyback dipasang antiparalel pada motor untuk membatasi lonjakan saat motor dimatikan; polaritas dan rating harus diperiksa guru berdasarkan pompa serta rancangan driver. Jangan menganggap keluaran USB SCC tersedia sebelum memeriksa manual dan mengukurnya.
- **Kegiatan:** cocokkan spesifikasi komponen, baca diagram sambungan, dan buat checklist perakitan serta pengujian. Identifikasi dioda paralel motor: katoda ke positif dan anoda ke negatif saat operasi normal.
- **Hasil belajar:** siswa dapat menelusuri diagram sistem dan menyebut pemeriksaan yang harus dilakukan sebelum daya diberikan.
- **Catatan keselamatan:** 1N4007 tidak otomatis cocok untuk semua pompa—periksa arus kerja dan arus awal. Ikuti manual SCC untuk urutan penyambungan panel/baterai. Guru memeriksa rating dioda, driver, kabel, baterai, panel, dan SCC.

## Pertemuan 7: Desain mekanik—kebutuhan dan sketsa
- **Materi:** ukuran komponen, akses servis, penahan kabel, posisi sensor, dan jalur air.
- **Materi inti:** ukur panjang, lebar, tinggi, lubang pemasangan, konektor, dan ruang untuk jari/alat servis. Sisakan ruang kabel agar tidak tertekuk atau tertarik. Rencanakan jalur air agar kebocoran tidak mengarah ke ESP32, baterai, atau sambungan listrik.
- **Kegiatan:** ukur komponen; buat sketsa layout enclosure dan tandai bukaan kabel/USB serta ruang servis.
- **Hasil belajar:** siswa dapat membuat sketsa berskala sederhana dan menjelaskan alasan penempatan komponen.

## Pertemuan 8: Desain mekanik—model 3D dan tinjauan
- **Materi:** pemodelan dasar di Tinkercad, toleransi ukuran, bukaan, dan perlindungan dari cipratan.
- **Materi inti:** ubah ukuran nyata menjadi sketsa/model, buat dinding dan bukaan dengan jarak yang cukup, lalu cocokkan model dengan komponen sebelum dicetak. Toleransi printer dan bahan dapat membuat hasil cetak berbeda dari model. Box 3D biasa, lubang USB terbuka, dan sambungan kabel tanpa gland/gasket tidak dapat dianggap kedap air.
- **Kegiatan:** buat model enclosure, tinjau rancangan dengan kelompok lain, dan perbaiki ukuran sebelum dicetak/dipasang.
- **Hasil belajar:** siswa dapat menghasilkan model yang sesuai ukuran komponen dan menunjukkan jalur kabel yang aman.
- **Catatan:** desain atau cetakan 3D tidak otomatis tahan cuaca/IP65. Perlindungan perlu dinilai bersama gasket, cable gland, bahan, dan pengujian rakitan.

## Pertemuan 9: Perakitan jalur daya dan kendali
- **Materi:** jalur sinyal ESP32, jalur daya pompa, suplai 5 V untuk board, dan suplai motor sesuai spesifikasi.
- **Materi inti:** ikuti diagram yang sudah diverifikasi, jangan mengandalkan warna kabel saja. Periksa bahwa kontak relay/driver mampu menangani tegangan dan arus pompa; pastikan dioda dipasang pada beban motor sesuai diagram. Uji berurutan: inspeksi tanpa daya → suplai ESP32 dan sensor → kendali relay tanpa pompa → pompa dengan pengawasan. Ground bersama hanya dipasang bila diperlukan oleh topologi rangkaian/modul dan diagramnya.
- **Kegiatan:** rakit atau periksa wiring sesuai diagram; verifikasi polaritas, sekering, rating relay/driver dan dioda. Uji sensor/logika dahulu, relay berikutnya, lalu pompa dengan pengawasan.
- **Hasil belajar:** siswa dapat menelusuri jalur sinyal/daya dan memakai checklist sebelum pengujian.
- **Bukti belajar:** checklist yang ditandatangani siswa dan guru.

## Pertemuan 10: Pemasangan box, pipa, dan sensor
- **Materi:** pemasangan komponen, kebocoran, arah aliran, dan posisi sensor.
- **Materi inti:** kenali sisi masuk dan keluar pompa dari tanda/manual; pastikan tandon cukup tinggi/posisinya sesuai kebutuhan pompa. Tempatkan sensor di area akar tetapi tidak tepat di bawah titik tetes agar pembacaan tidak hanya mencerminkan air yang baru keluar. Uji aliran dan kebocoran lebih dahulu dengan listrik serta sambungan elektronik dijauhkan dari air.
- **Kegiatan:** pasang komponen pada box; sambungkan jalur air dari tandon (misalnya galon 19 L), melalui pompa DC 12 V, menuju selang PE 5/16 inci dan titik tetes. Tempatkan dua sensor di pot/area uji (misalnya 80 × 40 cm) dan tandai posisinya.
- **Hasil belajar:** siswa dapat menjelaskan posisi sensor dan titik tetes; jalur air terpasang tanpa kebocoran dekat sambungan listrik.
- **Catatan:** jangan menyebut box IP65 kecuali rakitan beserta semua bukaannya memenuhi dan lulus pengujian yang relevan.

## Pertemuan 11: Kalibrasi lapangan dan debugging
- **Materi:** variasi tanah, pembacaan sensor, catu daya sesuai spesifikasi board, sambungan longgar, serta gejala restart/hang.
- **Materi inti:** debugging dilakukan dengan urutan: amati gejala → buat dugaan → ubah satu hal → ukur/tes ulang → catat hasil. Nilai sensor tidak stabil dapat berasal dari posisi, kabel, atau suplai; ESP32 yang restart dapat terkait catu daya atau gangguan beban motor. Pengukuran listrik dilakukan guru pada titik uji yang aman, memakai alat dan rentang ukur yang tepat.
- **Kegiatan:** kalibrasi ulang pada tanah di pot; guru mengukur titik uji yang aman dan memeriksa apakah keluaran 5 V yang dipakai memang tersedia/stabil. Jalankan sejumlah siklus yang ditentukan guru; hentikan bila ada panas berlebih, bau, suara tidak normal, kebocoran, atau kabel longgar.
- **Hasil belajar:** siswa dapat memakai data untuk mengidentifikasi satu masalah, melakukan perbaikan yang disetujui guru, dan mencatat hasil uji.
- **Bukti belajar:** tabel kalibrasi dan log pengujian.

## Pertemuan 12: Uji akhir, post-test, dan presentasi
- **Kegiatan:** demonstrasikan sistem dengan aman; presentasikan diagram, aturan mulai/berhenti, kalibrasi, hasil uji, dan satu masalah yang berhasil diperbaiki.
- **Materi inti:** presentasi ilmiah sederhana memuat tujuan, diagram, metode uji, data sebelum/sesudah, hasil, keterbatasan, dan usulan perbaikan. Sistem yang berhasil menyala sekali belum membuktikan sistem andal; jelaskan jumlah siklus yang diuji dan kondisi pengujiannya.
- **Hasil belajar:** siswa dapat menjelaskan kapan sistem mulai menyiram, mengapa pompa berpulsa, kapan sensor dibaca ulang, dan kapan sistem berhenti.
- **Penilaian:** pemahaman konsep, program/kalibrasi, keselamatan perakitan, pengujian berbasis data, dan presentasi.

---

## Lampiran 1: Pre-test (Pertemuan 1)

Gunakan penilaian diri (**Paham / Sedikit paham / Kurang tahu / Tidak tahu**) dan pertanyaan diagnostik. Tekankan bahwa pre-test bukan ujian untuk nilai akhir.

### Penilaian diri
1. Saya dapat menjelaskan secara sederhana bagaimana panel surya menghasilkan listrik.
2. Saya tahu bahwa polaritas baterai perlu diperiksa sebelum disambungkan.
3. Saya dapat menjelaskan fungsi ESP32 dalam sistem otomatis.
4. Saya dapat memberi contoh aturan “jika kondisi terpenuhi, maka lakukan sesuatu”.
5. Saya tahu cara menghitung rata-rata dua angka.

### Pertanyaan diagnostik
1. Jika sensor memberikan angka berbeda pada tanah kering dan lembap, informasi apa yang dapat diperoleh?
2. Mengapa pompa tidak boleh disambungkan langsung ke GPIO ESP32?
3. Apa yang harus dilakukan sebelum mengubah kabel pada rangkaian?

## Lampiran 2: Panduan post-test dan presentasi (Pertemuan 12)

Terima jawaban dengan kata-kata sendiri selama konsep utamanya benar.

1. Apa fungsi dioda proteksi pada motor DC, dan mengapa rating-nya perlu dicocokkan dengan pompa?
2. Bagian program mana yang mengatur pulsa 5 detik dan jeda 55 detik? Kapan sensor dibaca ulang?
3. Kondisi apa yang membuat sistem mulai menyiram, dan kondisi apa yang membuatnya berhenti?
4. Apa kelemahan memakai rata-rata jika dua sensor menunjukkan kelembapan yang berbeda jauh?
5. Masalah apa yang ditemukan saat uji, data apa yang membantu menemukannya, dan bagaimana perbaikannya?
6. Pemeriksaan keselamatan apa yang dilakukan sebelum sistem diberi daya?

## Lampiran 3: Rubrik penilaian proyek akhir

| Aspek | Bobot | Indikator |
|---|---:|---|
| Pemahaman konsep dan logika | 25% | Menjelaskan sensor, ambang, pulsa, jeda, dan kondisi berhenti. |
| Pemrograman dan kalibrasi | 25% | Program berjalan; nilai sensor dan kalibrasi didokumentasikan. |
| Perakitan dan keselamatan | 25% | Mengikuti prosedur, wiring sesuai diagram, dan mengenali kondisi berbahaya. |
| Pengujian dan presentasi | 25% | Menyajikan data uji, menjelaskan masalah/perbaikan, dan berkomunikasi jelas. |

## Lampiran 4: Contoh bahan latihan pemrograman

### Mengubah nilai sensor menjadi persentase relatif

Nilai `rawDry` dan `rawWet` harus diisi dari hasil kalibrasi sensor yang digunakan. Nilai dapat berbeda antar sensor dan jenis tanah.

```cpp
float toMoisturePercent(int raw, int rawDry, int rawWet) {
  if (rawDry == rawWet) return 0.0;

  float percent = 100.0 * (raw - rawDry) / (rawWet - rawDry);
  if (percent < 0.0) percent = 0.0;
  if (percent > 100.0) percent = 100.0;
  return percent;
}
```

Jika memakai dua sensor, siswa dapat membandingkan rata-rata keduanya dengan pembacaan terendah. Pilihan tersebut harus sesuai tujuan penyiraman karena rata-rata bisa menyembunyikan pot yang kering.

### Alur keputusan penyiraman

Pseudocode berikut menjelaskan urutan, bukan program siap unggah. Fungsi baca sensor dan kendali relay perlu disesuaikan dengan rangkaian; kondisi ON relay dapat aktif-HIGH atau aktif-LOW.

```text
set watering = false
ulang terus:
    baca kelembapan
    jika watering == false dan kelembapan < 60:
        set watering = true

    jika watering == true:
        nyalakan pompa selama 5 detik
        matikan pompa
        tunggu 55 detik agar air meresap
        baca kelembapan kembali
        jika kelembapan >= 85:
            set watering = false
```
