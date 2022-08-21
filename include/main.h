#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include <TFT_eSPI.h>

#define PIN_LED1 12
#define PIN_LED2 13

extern TFT_eSPI tft;

void inline initTFT() {
  tft.begin();
  tft.setRotation(3);
  tft.setTextFont(2);
  tft.fillScreen(TFT_BLACK);
}

void inline initLEDs() {
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED1, LOW);
  digitalWrite(PIN_LED2, LOW);
}

#endif