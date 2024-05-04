#include "DerbyUi.h"

extern const uint16_t logo[];

DerbyUi::DerbyUi() {
}

void DerbyUi::displayCountdown(String val) {
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(7);
  M5.Lcd.setCursor(140, 10);
  M5.Lcd.print(val);
}

void DerbyUi::displayWifiInfo(const char *ssid, const char *pwd, const IPAddress *ip, const char *version) {
  display.clearDisplay();
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(50, 20);
  M5.Lcd.print("Wi-Fi Server");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(50, 60);
  M5.Lcd.print("SSID: ");
  M5.Lcd.print(ssid);
  M5.Lcd.setCursor(50, 80);
  M5.Lcd.print("PSWD: ");
  M5.Lcd.print(pwd);
  M5.Lcd.setCursor(50, 100);
  M5.Lcd.print("URL: ");
  M5.Lcd.print(*ip);
  M5.Lcd.setCursor(50, 120);
  M5.Lcd.print("Version: ");
  M5.Lcd.print(version);
}

void DerbyUi::displayRaceTimes(float raceTimes[], int lanes) {
  char text[50];
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(3);

  for (int i = 0; i < lanes; i++) {
    char c;
    switch(i)
    {
      case 0:
        c = 'G';
        break;
      case 1:
        c = 'I';
        break;
      case 2:
        c = 'R';
        break;
      case 3:
        c = 'L';
        break;
      default:
        c = ' ';
        break;
    }
    sprintf(text, "Lane %c: %2.3f", c, raceTimes[i]);
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