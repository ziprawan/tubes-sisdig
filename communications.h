
#ifndef _COMMS_H_
#define _COMMS_H_

#include <SPI.h>
#include "config.h"

#define latchOn() bitSet(PORTB, LATCH_PIN_B)
#define latchOff() bitClear(PORTB, LATCH_PIN_B)

// Menginisiasi komunikasi dengan melakukan
// konfigurasi terhadap SPI (Serial Peripheral Interface)
void init_comm();

// Mengirim data sebesar 16 bit (2-byte) ke SPI
void send_data(uint16_t data);

// Mengirim data kosong ke SPI guna mengosongkan/membersihkan data
void clear_data();

#endif