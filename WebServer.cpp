#include "WebServer.h"

const IPAddress ip(192, 168, 0, 1);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);
const char ssid[] = "DerbyTrack";
const char password[] = "12345678";

WebServer::WebServer()
{
}

bool WebServer::init()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(ip, gateway, subnet);
  WiFi.begin();
}
