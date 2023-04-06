#include <M5Stack.h>
#include "RaceController.h"

#define SENSOR_1 3
#define SENSOR_2 1
#define SENSOR_3 16
#define SENSOR_4 17
#define BUTTON_A 39
#define BUTTON_B 38
#define BUTTON_C 37

RaceController gRaceController;

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

  if (buttonCPressed) {
    buttonCPressed = false;
    laneComplete = 0;
    resultsUpdated = false;
    gRaceController.init();
  }

  if (resultsUpdated) {
    gRaceController.displayResults();
    resultsUpdated = false;
  }

  M5.Speaker.update();
  //delay(500);
}




/*String parseGET(String str)
{
  String tmp = "";
  for (int i = 0, j = 0; i < str.length(); i++)
  {
    if (str[i] == ' ') j++;
    if (j == 1)
    {
      if (str[i] != ' ') tmp += str[i];
    }
    if (j == 2) break;
  }
  return tmp;
}*/

//bool gStartRace = false;
//String M5STACK_DATA;
//WiFiServer gServer(80);


//  gServer.begin();

/*M5.Lcd.setBrightness(100);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(50, 20);
  M5.Lcd.print("Wi-Fi Server");
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(50, 60);
  M5.Lcd.print("SSID: ");
  M5.Lcd.print(cSsid);
  M5.Lcd.setCursor(50, 80);
  M5.Lcd.print("PSWD: ");
  M5.Lcd.print(cPassword);
  M5.Lcd.setCursor(50, 100);
  M5.Lcd.print("URL: ");
  M5.Lcd.print(cIp);*/

//String currentString = "";
//bool readyResponse = false;
//WiFiClient client = gServer.available();

/*while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      if (c != '\r')
      {
        if (c != '\n')
        {
          currentString += c;
        }
      }
      else
      {
        readyResponse = true;
      }

      if (readyResponse)
      {
        String GET = parseGET(currentString);

        client.println("HTTP/1.1 200 OK");
        client.println();

        if (GET == "/update")
        {
          client.print("<html>");
          client.print("<head>");
          client.print("<meta http-equiv=\"Refresh\" content=\"1\"/>");
          client.print("<script type=\"text/javascript\">");
          client.print("var M5STACK_DATA = \"");
          client.print(M5STACK_DATA);
          client.print("\";");
          client.print("</script>");
          client.print("</head>");
          client.print("</html>");
        }
        else
        {
          client.print("<html>");
          client.print("<head>");
          client.print("<meta name=\"viewport\" content=\"width=device-width; initial-scale=1.0; maximum-scale=1.0; user-scalable=0;\" />");
          client.print("<script type=\"text/javascript\">");
          client.print("setInterval(function(){document.getElementById(\"M5STACK_DATA\").innerHTML = window.frames[0].M5STACK_DATA;}, 1000);");
          client.print("</script>");
          client.print("</head>");
          client.print("<body>");
          client.print("<h1>M5Stack</h1>");
          client.print("<h2>Wi-Fi Server</h2>");
          client.print("<hr>");
          client.print("<h3>Remote control:</h3>");
          client.print("<span>Note: please click on the button and look at the screen of the device</span>");
          client.print("<br><br>");

          if ((GET == "/off?") || (GET == "/"))
          {
            //M5.Lcd.drawBitmap(126, 120, 100, 100, (uint16_t *)lightOff);
            client.print("<form action=\"/on\">");
            client.print("<button type=\"submit\">Turn ON</button>");
          }
          else if (GET == "/on?")
          {
            //M5.Lcd.drawBitmap(126, 120, 100, 100, (uint16_t *)lightOn);
            client.print("<form action=\"/off\">");
            client.print("<button type=\"submit\">Turn OFF</button>");
          }
          
          client.print("</form>");
          client.print("<hr>");
          client.print("<h3>Remote monitor:</h3>");
          client.print("<span>Note: please press and hold any three buttons on the device</span>");
          client.print("<br>");
          client.print("> <span id=\"M5STACK_DATA\"></span>");
          client.print("<iframe src=\"/update\" hidden=\"true\"></iframe>");
          client.print("</body>");
          client.print("</html>");
        }

        client.println();
        client.println();
        readyResponse = false;
        currentString = "";
        break;
      }
    }
  }*/
