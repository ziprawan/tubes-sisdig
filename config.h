#ifndef __CONFIG_H_
#define __CONFIG_H_

#define LATCH_PIN 10
#define CLOCK_PIN 13
#define DATA_PIN 11

#define CLOCK 9
#define RESET 8
#define PIN_OFF 8

#define LATCH_PIN_B LATCH_PIN - PIN_OFF
#define CLOCK_PIN_B CLOCK_PIN - PIN_OFF
#define DATA_PIN_B DATA_PIN - PIN_OFF

// 20 fps or something like that, you call it
#define REFRESH_RATE_HZ 20
#define RENDER_DELAY_MS 1000 / REFRESH_RATE_HZ

#endif
