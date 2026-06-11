#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <Arduino.h>
#include <SPI.h>
#include "config.h"
#include "communications.h"
#include "font.h"

void init();

void init_display(unsigned long data_len);

void render(char data[]);

#endif