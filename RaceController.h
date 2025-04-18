#ifndef _RACECONTROLLER_H_
#define _RACECONTROLLER_H_

#include <M5Stack.h>
#include "Module_4RELAY.h"
#include "Ticker.h"

#define LANE_COUNT (4)

#define RELAY_RED 0
#define RELAY_YELLOW 1
#define RELAY_GREEN 2
#define RELAY_START 3
#define RELAY_NONE 4
#define RELAY_CANCEL 5

typedef void (*callback_t)(void);

class RaceController {
public:
  RaceController();
  bool init();
  void captureTime(int lane);
  void updateResults();
  void directControl(int cmd);
  bool startRace(callback_t raceStarted);
  void displayWifiInfo(const char *ssid, const char *pwd, const IPAddress *ip, const char *version);
  float runTimes[LANE_COUNT];
private:
  unsigned long endTime[LANE_COUNT];
};

#endif
