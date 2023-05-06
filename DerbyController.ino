#include <M5Stack.h>
#include "RaceController.h"
#include "WebServer.h"

#define SENSOR_1 3
#define SENSOR_2 1
#define SENSOR_3 16
#define SENSOR_4 2
#define BUTTON_A 39
#define BUTTON_B 38
#define BUTTON_C 37

RaceController gRaceController;
WebServer gWebServer;

static bool buttonAPressed = false;
static bool buttonBPressed = false;
static bool buttonCPressed = false;
static bool resultsUpdated = false;
static uint8_t laneComplete = 0xFF;

void IRAM_ATTR buttonA_Press() {
  buttonAPressed = true;
}

void IRAM_ATTR buttonB_Press() {
  buttonBPressed = true;
}

void IRAM_ATTR buttonC_Press() {
  buttonCPressed = true;
}

void IRAM_ATTR sensor1_Trigger() {
  if (laneComplete & 0x01) return;
  gRaceController.captureTime(0);
  laneComplete |= 0x01;
  resultsUpdated = true;
}

void IRAM_ATTR sensor2_Trigger() {
  if (laneComplete & 0x02) return;
  gRaceController.captureTime(1);
  laneComplete |= 0x02;
  resultsUpdated = true;
}

void IRAM_ATTR sensor3_Trigger() {
  if (laneComplete & 0x04) return;
  gRaceController.captureTime(2);
  laneComplete |= 0x04;
  resultsUpdated = true;
}

void IRAM_ATTR sensor4_Trigger() {
  if (laneComplete & 0x08) return;
  gRaceController.captureTime(3);
  laneComplete |= 0x08;
  resultsUpdated = true;
}

void raceStarted(void) {
  laneComplete = 0;
}

void setup() {
  m5.begin();

  gRaceController.init();
  gWebServer.init();

  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
  pinMode(SENSOR_3, INPUT_PULLUP);
  pinMode(SENSOR_4, INPUT_PULLUP);

  attachInterrupt(BUTTON_A, buttonA_Press, FALLING);
  attachInterrupt(BUTTON_B, buttonB_Press, FALLING);
  attachInterrupt(BUTTON_C, buttonC_Press, FALLING);

  attachInterrupt(SENSOR_1, sensor1_Trigger, FALLING);
  attachInterrupt(SENSOR_2, sensor2_Trigger, FALLING);
  attachInterrupt(SENSOR_3, sensor3_Trigger, FALLING);
  attachInterrupt(SENSOR_4, sensor4_Trigger, FALLING);
}

void loop() {
  if (buttonAPressed) {
    buttonAPressed = false;
    laneComplete = 0;
    resultsUpdated = true;
    gRaceController.startRace(raceStarted);
  }

  if (buttonBPressed) {
    buttonBPressed = false;
     gRaceController.displayWifiInfo(gWebServer.getSsid(), gWebServer.getPassword(), gWebServer.getIp());
  }

  if (buttonCPressed) {
    buttonCPressed = false;
    laneComplete = 0;
    resultsUpdated = false;
    gRaceController.init();
  }

  if (resultsUpdated) {
    gRaceController.updateResults();
    resultsUpdated = false;
  }

  if (gWebServer.handleRequest(gRaceController.runTimes)) {
    buttonAPressed = true;
  }

  M5.Speaker.update();
}
