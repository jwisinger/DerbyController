#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_
#include "WiFi.h"

typedef enum WebCommand {
  None,
  Red,
  Yellow,
  Green,
  Go,
  Start
} WebCommand;

class WebServer {
public:
  WebServer();
  void init();
  WebCommand handleRequest(float runTimes[4]);
  const char *getSsid();
  const char *getPassword();
  const IPAddress *getIp();
private:
  bool getNextCharacter(WiFiClient *client);
};

#endif