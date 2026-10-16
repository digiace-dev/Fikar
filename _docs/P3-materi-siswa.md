# Materi Siswa — Desain Skematik dan PCB dengan EasyEDA

**Proyek:** sistem penyiraman otomatis berbasis ESP32 & panel surya · **Pertemuan 3**

Halo! Sekarang kamu akan merancang **skema** dan **papan (PCB)** sistem penyiraman di komputer menggunakan EasyEDA. Materi ini bisa kamu baca dan pelajari sendiri, lalu kerjakan langkah praktik dan checklist-nya.

---

## Setelah mempelajari ini, kamu bisa

- Menjelaskan perbedaan skema (hubungan listrik) dan layout PCB (bentuk fisik papan).
- Mengenali simbol resistor, kapasitor, dioda, transistor, modul relay, buzzer, dan header/konektor.
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
| Resistor | Zigzag/kotak | Pembatas arus (di dalam modul relay; opsional di skema) |
| Kapasitor | Dua garis sejajar | Meratakan tegangan (opsional) |
| Dioda | Segitiga + garis | D1 (flyback) melindungi pompa dari lonjakan |
| Transistor NPN | Tanda panah keluar | Saklar elektronik di dalam modul relay |
| Modul relay | Kotak dengan kumparan + kontak | Pengendali daya 12V ke pompa (COM/NO) |
| Buzzer | Setengah lingkaran | Indikator suara status penyiraman |
| Header/konektor | Kotak dengan pin | Titik hubung sensor, ESP32, buzzer, dan pompa |

### 3. Net, net label, dan simbol daya

- **Wire** menghubungkan dua pin secara langsung.
- **Net label** memberi nama pada sambungan. Dua pin dengan label sama dianggap terhubung tanpa kawat panjang.
- **GND** dan **VCC** adalah simbol daya yang sekaligus net label.
- Contoh: pin AOUT Sensor 1 diberi label `SENSOR1_AOUT`, lalu label sama dipakai di pin GPIO34 ESP32 — keduanya dianggap tersambung. Sensor 2 memakai label `SENSOR2_AOUT` menuju GPIO35.

### 4. Skema acuan proyek

Skema sistem penyiraman terdiri atas empat kelompok: dua sensor, ESP32, indikator (buzzer), dan modul relay menuju pompa.

```text
SENSOR 1 (J1)                     ESP32 (U1)
  VCC  ─────────────────────────── 5V
  GND  ─────────────────────────── GND
  AOUT ─────────────────────────── GPIO34 (analog, ADC1)

SENSOR 2 (J2)
  VCC  ─────────────────────────── 5V
  GND  ─────────────────────────── GND
  AOUT ─────────────────────────── GPIO35 (analog, ADC1)

BUZZER (BZ1) — buzzer aktif 5V
  VCC  ─────────────────────────── 5V
  GND  ─────────────────────────── GND
  I/O  ─────────────────────────── GPIO27

MODUL RELAY (K1) — 1-channel 5V optocoupler (active-low)
  VCC  ─────────────────────────── 5V
  GND  ─────────────────────────── GND
  IN   ─────────────────────────── GPIO26

Sisi beban 12V (terpisah dari sisi kendali 5V):
  12V (SCC Load +) ── COM K1 ── NO K1 ── Pompa (+)
  Pompa (−) ── GND 12V
  D1 (1N4007) paralel-terbalik pada terminal pompa:
    katoda D1 → Pompa (+); anoda D1 → Pompa (−)
```

Sisi kendali (GPIO → modul relay) dan sisi beban (relay → pompa, 12V) tetap dipisah. Dioda D1 dipasang langsung pada terminal pompa (bukan pada kumparan relay).

### 5. Dari skema ke PCB

Setelah skema selesai, EasyEDA dapat **mengubah skema menjadi PCB** (Convert to PCB):

- Setiap simbol dipetakan ke **footprint** (bentuk fisik kaki komponen).
- Sambungan muncul sebagai **ratnest**: garis tipis yang menunjukkan kaki mana yang perlu disambung, tetapi belum di-routing.
- Ratnest hanyalah petunjuk; jalur tembaga yang sebenarnya dibuat lewat routing.

### 6. Penempatan komponen dan routing

- **Penempatan:** kelompokkan komponen menurut fungsi, bukan urutan skema. Perhatikan arah komponen berpolaritas (dioda) dan posisi pin modul relay/buzzer.
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
4. Beri label net: `GND`, `5V`, `12V`, sinyal sensor (2 buah), sinyal relay, dan sinyal buzzer.
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
| Header sensor 1 (J1) | Capacitive Soil Moisture v1.2 | |
| Header sensor 2 (J2) | Capacitive Soil Moisture v1.2 | |
| Header/konektor ESP32 | ESP32 DevKit V1 (30 pin) | |
| Modul Relay K1 | 1-channel 5V optocoupler | |
| Buzzer BZ1 | Aktif 5V | |
| Dioda D1 | 1N4007 | |
| Terminal/konektor pompa | DC 12V | |

### Checklist skema

- [ ] Kedua sensor (VCC, GND, AOUT) terhubung ke 5V, GND, dan pin ADC yang benar (GPIO34 & GPIO35).
- [ ] Net label GND, 5V, dan 12V tidak tertukar.
- [ ] Sinyal relay (IN) menuju GPIO26 dan buzzer (I/O) menuju GPIO27.
- [ ] Dioda D1 terpasang paralel-terbalik pada terminal pompa dengan polaritas yang benar.
- [ ] Sisi beban (relay → pompa) memakai jalur 12V, terpisah dari sisi kendali 5V.

### Checklist layout dan DRC

- [ ] Semua komponen ditempatkan dan tidak saling bertumpuk.
- [ ] Komponen berpolaritas menghadap arah yang benar.
- [ ] Ratnest kosong (semua sambungan sudah di-routing).
- [ ] DRC dijalankan dan error sudah diperbaiki.

---

## Pertanyaan refleksi

1. Apa perbedaan skema dan layout PCB?
2. Apa fungsi net label, dan mengapa dipakai?
3. Mengapa dioda D1 (flyback) perlu dipasang paralel-terbalik pada terminal pompa?
4. Apa yang kamu periksa sebelum desain PCB dianggap selesai?

---

## Rangkuman

- Alur pengerjaan: **skema** (simbol + net) → **PCB** (footprint + ratnest) → **penempatan** → **routing** → **DRC**.
- Sistem memakai **dua sensor** (GPIO34 & GPIO35), **modul relay** (GPIO26), dan **buzzer** (GPIO27).
- **Net label** membuat skema rapi; GND/5V/12V tidak boleh tertukar.
- Perhatikan **polaritas** dioda D1 pada pompa; **DRC** harus bersih.

---

## Catatan keselamatan

1. Gunakan skema acuan dan nilai komponen yang sudah diperiksa guru.
2. Perhatikan polaritas dioda D1 dan arah terminal pompa; pemasangan terbalik dapat merusak komponen saat dirakit.
3. Simpan proyek secara teratur dan beri nama file yang jelas.
4. Fabrikasi, ekspor Gerber, dan penyolderan hanya dilakukan dengan pengawasan guru.
