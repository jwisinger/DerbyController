#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_
#include "WiFi.h"

typedef enum WebCommand {
  None,
  Red,
  Yellow,
  Green,
  Go,
  Start,
  Cancel
} WebCommand;

class WebServer {
public:
  WebServer();
  void init();
  WebCommand handleRequest(float runTimes[4], int switchPressed[3]);
  const char *getSsid();
  const char *getPassword();
  const IPAddress *getIp();
private:
  bool getNextCharacter(WiFiClient *client);
};

#endif