#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_
#include "WiFi.h"

class WebServer {
public:
  WebServer();
  void init();
  void handleRequest(float runTimes[4]);
  const char *getSsid();
  const char *getPassword();
  const IPAddress getIp();
private:
  bool getNextCharacter(WiFiClient *client);
};

#endif