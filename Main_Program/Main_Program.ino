#include<WiFi.h>
#include<TimeLib.h>
#include <WiFiUdp.h>
#include "HX711.h"
#include<ESP32Servo.h>

#define DOUT  23
#define CLK  19
//=====================WiFi==================================
const char* ssid = "NOMOREDOTAFORTOMMOROW"; // IT-DEV
const char* password = "N0m0r3d0t4";
//=====================Load Cell=============================
HX711 scale;
float calibration_factor = 334;

//=====================Servo=================================
Servo servo;
#define openServo 50
#define closeServo 0
#define serPin 4
//=====================Ultra Sonic===========================
#define echoPin 18
#define trigPin 5
//=====================NTP===================================
static const char ntpServerName[] = "pool.ntp.org";
const int timeZone = 7;
WiFiUDP Udp;
unsigned int localPort = 8888;
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
// ===============variable Jadwal ===========================
unsigned int jHour[5];
unsigned int jMinute[5];
unsigned int jPortion[5];
unsigned int sizeArray;
bool bFeed = true;
void setup() {
  Serial.begin(115200);
  wifi();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.setPeriodHertz(50);// Standard 50hz servo

  scale.begin(DOUT, CLK);
  scale.set_scale();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
  delay(1000);
  jHour[0] = 7;
  jHour[1] = 12;
  jHour[2] = 21;
  jMinute[0] = 0;
  jMinute[1] = 0;
  jMinute[2] = 55;
  jPortion[0] = 100;
  jPortion[1] = 100;
  jPortion[1] = 100;
  sizeArray = sizeof(jHour) / sizeof(jHour[0]);
  Serial.print("size Array =");
  Serial.println(sizeArray);
}
unsigned long  prevPrint;
void loop() {
  wifi_reconnect();
  if ( year() == 1970 )
  {
    ntpBegin();
  }
  String timeNow = getFulldate();
  if ( millis() - prevPrint >= 1000)
  {
    Serial.print("Time Now = ");
    Serial.println(timeNow);
    prevPrint = millis();
  }
  unsigned long H = hour();
  unsigned long M = minute();
  for ( int i = 0; i <= sizeArray; i++)
  {
    if ( H == jHour[i] && M == jMinute[i] && bFeed)
    {
      Serial.println("Kasih Pakan");
      feed(jPortion[i]);
      bFeed = false;

    }
    else if (H == jHour[i] && M == jMinute[i] + 5 && !bFeed)
    {
      Serial.println("boolean menjadi True");
      bFeed = true;
    }
  }
}
