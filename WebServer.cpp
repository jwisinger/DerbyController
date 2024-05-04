#include "WebServer.h"

const IPAddress ip(192, 168, 0, 1);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);
const char ssid[] = "DerbyTrack";
const char password[] = "12345678";

WiFiServer server(80);
char rx[100];
int rxPtr = 0;

WebServer::WebServer() {
  rxPtr = 0;
}

void WebServer::init() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.begin();
  server.begin();
}

bool WebServer::getNextCharacter(WiFiClient *client) {
  char c = client->read();
  if (c == '\r') return true;
  else if (c != '\n') {
    if (rxPtr < sizeof(rx) - 1) rx[rxPtr++] = c;
  }
  return false;
}

const char *WebServer::getSsid()
{
  return ssid;
}

const char *WebServer::getPassword()
{
  return password;
}

const IPAddress *WebServer::getIp()
{
  return &ip;
}

bool WebServer::handleRequest(float runTimes[4]) {
  bool start = false;
  char raceTimes[100];
  WiFiClient client = server.available();

  while (client.connected())  // DOES CONNECTED MEAN A QUICK WEB MESSAGE, OR IS IT STUCK IN THIS LOOP A LONG TIME?
  {
    if (client.available()) {
      if (getNextCharacter(&client)) {
        char *msg = rx + 4;  // Skip over first 4 bytes "GET "
        *(strpbrk(msg, " ")) = 0;
        client.println("HTTP/1.1 200 OK");
        client.println();

        if (!strcmp("/start", msg)) {
          client.print("Started");
          start = true;
        } else if (!strcmp("/read", msg)) {
          snprintf(raceTimes, sizeof(raceTimes), "Times %f,%f,%f,%f", runTimes[0], runTimes[1], runTimes[2], runTimes[3]);
          client.print(raceTimes);
        }
        client.println();
        rxPtr = 0;
        break;
      }
    }
  }
  return start; 
}
