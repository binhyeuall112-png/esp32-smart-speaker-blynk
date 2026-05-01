#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Speaker"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

char ssid[] = "wifiname";
char pass[] = "password";

HardwareSerial mySerial(2);
DFRobotDFPlayerMini player;

BlynkTimer timer;

// PLAY
BLYNK_WRITE(V0)
{
  if(param.asInt()==1)
  {
    player.start();
    Blynk.virtualWrite(V0,0);
  }
}

// PAUSE
BLYNK_WRITE(V1)
{
  if(param.asInt()==1)
  {
    player.pause();
    Blynk.virtualWrite(V1,0);
  }
}

// NEXT
BLYNK_WRITE(V2)
{
  if(param.asInt()==1)
  {
    player.next();
    Blynk.virtualWrite(V2,0);
  }
}

// PREVIOUS
BLYNK_WRITE(V3)
{
  if(param.asInt()==1)
  {
    player.previous();
    Blynk.virtualWrite(V3,0);
  }
}

// VOLUME
BLYNK_WRITE(V4)
{
  int vol = param.asInt();   //0-30
  player.volume(vol);
}

void setup()
{
  Serial.begin(115200);

  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16 TX=17

  if(player.begin(mySerial))
  {
    Serial.println("DFPlayer OK");
    player.volume(20);
  }
  else
  {
    Serial.println("DFPlayer Error");
  }

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();
}