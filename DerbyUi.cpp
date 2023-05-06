#include "DerbyUi.h"

extern const uint16_t logo[];

DerbyUi::DerbyUi() {
}

void DerbyUi::displayCountdown(String val) {
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(7);
  M5.Lcd.setCursor(30, 10);
  M5.Lcd.print(val);
}

void DerbyUi::displayRaceTimes(float raceTimes[], int lanes) {
  char text[50];
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(3);

  for (int i = 0; i < lanes; i++) {
    sprintf(text, "Lane %d: %2.3f", i + 1, raceTimes[i]);
    M5.Lcd.setCursor(45, 70 + (i * 25));
    M5.Lcd.print(text);
  }
}

void DerbyUi::init() {
  display.init();
  display.drawBitmap(0, 0, 320, 240, logo);
  buttonStart.initButton(&display, 65, 220, 65, 40, TFT_GOLD, TFT_DARKGREEN, TFT_WHITE, "Start", 1.8);
  buttonStart.drawButton();
  buttonInfo.initButton(&display, 160, 220, 65, 40, TFT_GOLD, TFT_DARKGREEN, TFT_WHITE, "Info", 1.8);
  buttonInfo.drawButton();
  buttonC.initButton(&display, 255, 220, 65, 40, TFT_GOLD, TFT_DARKGREEN, TFT_WHITE, "Clear", 1.8);
  buttonC.drawButton();
}