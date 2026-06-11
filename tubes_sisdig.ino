#include "display.h"

char text_msg[] = "Hello neighbros";

void setup()
{
  // Aktifin port serial buat debugging purposes
  Serial.begin(9600);

  // Bikin mode pin jadi OUTPUT
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(RESET, OUTPUT);

  // Reset
  digitalWrite(RESET, HIGH);
  digitalWrite(RESET, LOW);

  init_display(sizeof(text_msg));
}

void loop()
{
  render(text_msg);
}