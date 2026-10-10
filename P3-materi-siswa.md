# Materi Siswa — Desain Skematik dan PCB dengan EasyEDA

**Proyek:** sistem penyiraman otomatis berbasis ESP32 · **Pertemuan 3**

Halo! Sekarang kamu akan merancang **skema** dan **papan (PCB)** sistem penyiraman di komputer menggunakan EasyEDA. Materi ini bisa kamu baca dan pelajari sendiri, lalu kerjakan langkah praktik dan checklist-nya.

---

## Setelah mempelajari ini, kamu bisa

- Menjelaskan perbedaan skema (hubungan listrik) dan layout PCB (bentuk fisik papan).
- Mengenali simbol resistor, kapasitor, dioda, transistor, dan header/konektor.
- Membuat skema sederhana dengan net label, GND, dan VCC.
- Mengubah skema menjadi PCB dan menempatkan komponen.
- Melakukan routing dan menjalankan DRC.

---

## Istilah penting

| Istilah | Arti singkat |
|---|---|
| **Skema (schematic)** | Gambar hubungan listrik antarkomponen memakai simbol. |
| **Simbol** | Lambang komponen pada skema. |
| **Net / net label** | Nama sambungan; pin dengan label sama dianggap terhubung. |
| **GND / VCC** | Simbol daya (ground / catu positif). |
| **Footprint** | Bentuk fisik kaki komponen di papan. |
| **Layout PCB** | Tata letak komponen dan jalur tembaga di papan. |
| **Track** | Jalur tembaga yang menghubungkan pad. |
| **Via** | Lubang tembus untuk pindah lapisan. |
| **Ratnest** | Garis tipis penunjuk kaki yang perlu disambung. |
| **DRC** | Pemeriksa aturan desain otomatis. |

---

## Materi

### 1. Skema vs layout PCB

- **Skema** menjawab "apa terhubung ke apa", memakai **simbol**.
- **Layout PCB** menjawab "di mana letak komponen dan jalurnya", memakai **bentuk fisik** papan.
- Posisi komponen di skema **tidak sama** dengan posisi di papan.

### 2. Simbol komponen dasar

| Komponen | Simbol | Kegunaan dalam proyek |
|---|---|---|
| Resistor | Zigzag/kotak | Membatasi arus ke basis transistor |
| Kapasitor | Dua garis sejajar | Meratakan tegangan (opsional) |
| Dioda | Segitiga + garis | Flyback untuk melindungi dari lonjakan |
| Transistor NPN | Tanda panah keluar | Saklar elektronik penggerak relay |
| Header/konektor | Kotak dengan pin | Titik hubung sensor, ESP32, dan beban |

### 3. Net, net label, dan simbol daya

- **Wire** menghubungkan dua pin secara langsung.
- **Net label** memberi nama pada sambungan. Dua pin dengan label sama dianggap terhubung tanpa kawat panjang.
- **GND** dan **VCC** adalah simbol daya yang sekaligus net label.
- Contoh: pin OUT sensor diberi label `OUT_SENSOR`, lalu label sama dipakai di pin GPIO ESP32 — keduanya dianggap tersambung.

### 4. Skema acuan proyek

Skema sistem penyiraman terdiri atas tiga kelompok: sensor, ESP32, dan relay/driver menuju pompa.

```text
SENSOR (J1)                       ESP32 (J2)
  VCC  ─────────────────────────── 3V3
  GND  ─────────────────────────── GND
  OUT  ─────────────────────────── GPIO34 (analog)

ESP32 GPIO27 ── R1 (1 kΩ) ── Basis Q1 (NPN BC547)
VCC_5V ── kumparan Relay K1 ── Kolektor Q1
  D1 (1N4007) antiparalel dengan kumparan K1
  (katoda D1 ke VCC_5V, anoda D1 ke kolektor Q1)
Emitor Q1 ── GND

Kontak relay: COM ── VCC pompa; NO ── Pompa (+); Pompa (−) ── GND
```

Sisi kendali (GPIO → resistor → basis transistor) dan sisi beban (relay → pompa) tetap dipisah.

### 5. Dari skema ke PCB

Setelah skema selesai, EasyEDA dapat **mengubah skema menjadi PCB** (Convert to PCB):

- Setiap simbol dipetakan ke **footprint** (bentuk fisik kaki komponen).
- Sambungan muncul sebagai **ratnest**: garis tipis yang menunjukkan kaki mana yang perlu disambung, tetapi belum di-routing.
- Ratnest hanyalah petunjuk; jalur tembaga yang sebenarnya dibuat lewat routing.

### 6. Penempatan komponen dan routing

- **Penempatan:** kelompokkan komponen menurut fungsi, bukan urutan skema. Perhatikan arah komponen berpolaritas (dioda, transistor).
- **Routing:** tarik **track** untuk menghubungkan pad sesuai ratnest. Gunakan **via** untuk pindah lapisan.
- Jalur daya (VCC, GND) biasanya lebih lebar dari jalur sinyal; ikuti contoh guru.

### 7. Pemeriksaan dengan DRC

**DRC (Design Rule Check)** memeriksa aturan desain otomatis, misalnya jalur terlalu berdekatan, tidak terhubung, atau tumpang-tindih.

- Jalankan DRC setelah routing.
- Perbaiki setiap error/warning.
- Periksa **ratnest**: pastikan tidak ada sambungan yang belum di-routing.

### 8. Batas dan keselamatan

- Ini hanya **desain digital** di komputer; tidak ada tegangan berbahaya di meja kerja.
- Fabrikasi (pesan/cetak PCB) dan penyolderan dilakukan terpisah **dengan pengawasan guru**.

> 💡 **Coba cek:** Apa beda skema dan layout PCB?

<details>
<summary>Lihat jawaban</summary>

Skema = hubungan listrik (apa terhubung ke apa); layout = bentuk fisik papan (letak komponen + jalur tembaga).
</details>

> 💡 **Coba cek:** Apa itu ratnest pada tahap PCB?

<details>
<summary>Lihat jawaban</summary>

Garis tipis penunjuk kaki yang perlu disambung, sebelum jalur sebenarnya dibuat lewat routing.
</details>

---

## Langkah kerja praktik

1. Buka EasyEDA dan masuk ke akunmu.
2. Buat proyek baru, lalu mulai **skema** baru.
3. Tempatkan simbol sesuai skema acuan guru; hubungkan dengan wire atau net label.
4. Beri label net: `GND`, `VCC`/`3V3`/`5V`, sinyal sensor, dan sinyal kendali.
5. **Convert to PCB**; tempatkan komponen secara berkelompok sesuai fungsi.
6. **Routing** track sesuai ratnest.
7. Jalankan **DRC**; perbaiki error/warning.
8. Simpan proyek dan isi checklist di bawah.

---

## Lembar kerja / checklist

**Nama:** ____________________  **Kelompok:** __________  **Tanggal:** __________

### Daftar komponen

| Komponen | Nilai/spesifikasi | Footprint |
|---|---|---|
| Resistor R1 | | |
| Dioda D1 | | |
| Transistor Q1 | | |
| Relay K1 | | |
| Header sensor J1 | | |
| Header/konektor ESP32 | | |

### Checklist skema

- [ ] Semua pin sensor (VCC, GND, OUT) terhubung ke tempat yang benar.
- [ ] Net label GND dan VCC tidak tertukar.
- [ ] Sinyal sensor menuju pin analog ESP32 yang benar.
- [ ] Dioda D1 terpasang dengan arah (polaritas) yang benar.
- [ ] Transistor Q1 (basis, kolektor, emitor) terhubung sesuai skema acuan.

### Checklist layout dan DRC

- [ ] Semua komponen ditempatkan dan tidak saling bertumpuk.
- [ ] Komponen berpolaritas menghadap arah yang benar.
- [ ] Ratnest kosong (semua sambungan sudah di-routing).
- [ ] DRC dijalankan dan error sudah diperbaiki.

---

## Pertanyaan refleksi

1. Apa perbedaan skema dan layout PCB?
2. Apa fungsi net label, dan mengapa dipakai?
3. Mengapa dioda D1 perlu dipasang pada kumparan relay?
4. Apa yang kamu periksa sebelum desain PCB dianggap selesai?

---

## Rangkuman

- Alur pengerjaan: **skema** (simbol + net) → **PCB** (footprint + ratnest) → **penempatan** → **routing** → **DRC**.
- **Net label** membuat skema rapi; GND/VCC tidak boleh tertukar.
- Perhatikan **polaritas** dioda dan transistor; **DRC** harus bersih.

---

## Catatan keselamatan

1. Gunakan skema acuan dan nilai komponen yang sudah diperiksa guru.
2. Perhatikan polaritas dioda dan transistor; arah terbalik dapat merusak komponen saat dirakit.
3. Simpan proyek secara teratur dan beri nama file yang jelas.
4. Fabrikasi, ekspor Gerber, dan penyolderan hanya dilakukan dengan pengawasan guru.
