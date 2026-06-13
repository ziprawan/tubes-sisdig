#include "display.h"

// Karena jumlah kolom sudah pasti ada 16
// tipe data yang paling cocok adalah short
short screen_data[HEIGHT] = {0, 0, 0, 0, 0, 0};

// Panjang teks yang akan ditampilan dengan asumsi teks tidak akan memiliki panjang lebih dari 255
unsigned char text_length = 0;

// Nomor indeks karakter saat ini (yang lagi di-render di paling kanan)
int current_letter_idx = 0;
// Sisa panjang karakter yang belum di-render
int remaining_width = 0;
// Baris saat ini yang sedang di-render
int current_row = 0;
// Apakah sudah habis dan sedang membersihkan layar
bool is_clearing = false;
// Kapan terakhir teks bergerak dalam satuan ms
unsigned long last_scroll_ms = 0;

void init_display(unsigned long data_len)
{
  text_length = (unsigned char)data_len;
  init_comm();
}

void reset_row()
{
  digitalWrite(RESET, HIGH);
  digitalWrite(RESET, LOW);
  current_row = 0;
}

// Ganti ke baris berikutnya atau reset ketika sudah melebihi HEIGHT
void next_row()
{
  current_row++;
  if (current_row >= HEIGHT)
  {
    reset_row();
  }
  else
  {
    digitalWrite(CLOCK, HIGH);
    digitalWrite(CLOCK, LOW);
  }
}

void shiftData(char data[])
{
  if (remaining_width < 0)
  {
    current_letter_idx++;
    if (current_letter_idx >= text_length)
    {
      // TODO: Geser terus sampe kosong, terus ulangi dari awal
      current_letter_idx = 0; // Reset indeks ke awal
      remaining_width = 16;   // Banyak kolom
      is_clearing = true;
    }
    else
    {
      remaining_width = letter_width(data[current_letter_idx]);
    }
  }

  char col_data = is_clearing ? 0 : letter_data_at_column(data[current_letter_idx], current_row);

  for (int i = 0; i < HEIGHT; i++)
  {
    // Geser semuanya ke kiri sekali
    screen_data[i] <<= 1;
    // Masukin data barunya
    screen_data[i] |= (col_data >> (7 - i)) & 1;
  }
}

// Menampilkan data ke LED aseli biar keliatan
// Jujur gatau bisa apa ngga, ntar dicoba dah
void display_data()
{
  // Perubahan kondisional sudah dilakukan oleh next_row()
  for (; current_row < HEIGHT;)
  {
    send_data(screen_data[current_row++]);

    // Kata ChatGPT biar LED nya kelihatan nyala, di delay 100 us
    delayMicroseconds(100);

    clear_data();

    // Ganti baris
    next_row();
  }
}

void render(char data[])
{
  display_data();

  // Tunggu selama RENDER_DELAY_MS sebelum menggeser dan menambahkan
  // data baru ke dalam layar
  if (millis() - last_scroll_ms >= (unsigned long)RENDER_DELAY_MS)
  {
    shiftData(data);
    last_scroll_ms = millis();
  }
}