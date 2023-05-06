#include "RaceController.h"
#include "DerbyUi.h"

#define RELAY_RED 0
#define RELAY_YELLOW 1
#define RELAY_GREEN 2
#define RELAY_START 3

static MODULE_4RELAY relay;
static DerbyUi derbyUi;
static bool raceInProgress;
static Ticker onceTicker;
static unsigned long startTime = 0;
callback_t raceStartedFunction;

static void RaceCallback(int step) {
  relay.setAllRelay(false);

  if (!raceInProgress) return;

  switch (step) {
    case RELAY_RED:
      relay.setRelay(RELAY_YELLOW, true);
      onceTicker.once(1.0f, RaceCallback, RELAY_YELLOW);
      M5.Speaker.tone(512, 500);
      derbyUi.displayCountdown("2");
      break;
    case RELAY_YELLOW:
      relay.setRelay(RELAY_GREEN, true);
      onceTicker.once(1.0f, RaceCallback, RELAY_GREEN);
      M5.Speaker.tone(512, 500);
      derbyUi.displayCountdown("1");
      break;
    case RELAY_GREEN:
      relay.setRelay(RELAY_START, true);
      onceTicker.once(1.0f, RaceCallback, RELAY_START);
      M5.Speaker.tone(1024, 1000);
      startTime = micros();
      derbyUi.displayCountdown(" ");
      break;
    case RELAY_START:
      raceInProgress = false;
      raceStartedFunction();
      break;
  }
}

RaceController::RaceController() {
  raceInProgress = false;
}

bool RaceController::init() {
  raceInProgress = false;
  if (relay.begin(&Wire, MODULE_4RELAY_ADDR, 21, 22, 200000L)) {
    relay.setAllRelay(false);
    derbyUi.init();
    M5.Speaker.begin();
    return true;
  } else {
    return false;
  }
}

bool RaceController::startRace(callback_t raceStarted) {
  if (raceInProgress) return false;

  raceStartedFunction = raceStarted;
  raceInProgress = true;
  relay.setRelay(RELAY_RED, true);
  onceTicker.once(1.0f, RaceCallback, RELAY_RED);
  M5.Speaker.tone(512, 500);
  derbyUi.displayCountdown("3");
  for (int i = 0; i < sizeof(endTime) / sizeof(endTime[0]); i++) endTime[i] = 0;

  return true;
}

void RaceController::captureTime(int lane) {
  if (!raceInProgress) endTime[lane] = micros();
}

void RaceController::updateResults() {
  for (int i = 0; i < LANE_COUNT; i++) {
    if (endTime[i] == 0) runTimes[i] = 0.0f;
    else runTimes[i] = (endTime[i] - startTime) / 1000000.0;
  }

  derbyUi.displayRaceTimes(runTimes, LANE_COUNT);
}
