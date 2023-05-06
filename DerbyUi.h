#ifndef _DERBYUI_H_
#define _DERBYUI_H_

#include <M5Stack.h>
#include <M5GFX.h>
#include "Module_4RELAY.h"

class DerbyUi {
public:
  DerbyUi();
  void init();
  void displayCountdown(String val);
  void displayRaceTimes(float raceTimes[], int lanes);
  void displayWifiInfo(const char *ssid, const char *pwd, const IPAddress *ip);
private:
  M5GFX display;
  LGFX_Button buttonStart;
  LGFX_Button buttonInfo;
  LGFX_Button buttonC;
};

#endif
