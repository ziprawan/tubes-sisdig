#ifndef _FONT_H_
#define _FONT_H_

#define HEIGHT 6

// Mendapatkan indeks mulai dari keseluruhan data sebuah karakter
short int find_letter(char letter);

// Menghitung panjang byte dari sebuah karakter
char data_length(char width);

// Mendapatkan lebar karakter
char letter_width(char letter);

// Mengambil data karakter pada kolom tertentu
char letter_data_at_column(char letter, char column);

#endif