#include<WiFi.h>
#include<TimeLib.h>
#include <WiFiUdp.h>
#include "HX711.h"
#include<ESP32Servo.h>
#include "FS.h"
#include "SPIFFS.h"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DOUT  23
#define CLK  19
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
int jHour[5];
int jMinute[5];
int jPortion[5];
unsigned int sizeArray;
bool bFeed = true;
//==================Bylnk ===================================
BlynkTimer timer;
char auth[] = "ASeKdiRLR4DAZl64hYsZ7CBZOtFYQEKe";
char ssid[] = "Yusuf";
char pass[] = "p3rbanas";

uint32_t schedule[4];
const char* pathSchedule[] = {"/schedule1.txt", "/schedule2.txt", "/schedule3.txt"};
const char* pathPortion[] = {"/portion1.txt", "/portion2.txt", "/portion3.txt"};

float MinVolume = 4;
float MaxVolume = 10;
float Volume;
unsigned int VoulmePersen;
BLYNK_WRITE(V3)
{
  jPortion[0] = param.asInt();
  writeFile(SPIFFS, pathPortion[0],  String(jPortion[0]));
  Serial.print("Portion ");
  Serial.print("0");
  Serial.print(" : ");
  Serial.println(jPortion[0]);
}
BLYNK_WRITE(V4)
{
  jPortion[1] = param.asInt();
  writeFile(SPIFFS, pathPortion[1],  String(jPortion[1]));
  Serial.print("Portion ");
  Serial.print("1");
  Serial.print(" : ");
  Serial.println(jPortion[1]);
}
BLYNK_WRITE(V5)
{
  jPortion[2] = param.asInt();
  writeFile(SPIFFS, pathPortion[2],  String(jPortion[2]));
  Serial.print("Portion ");
  Serial.print("2");
  Serial.print(" : ");
  Serial.println(jPortion[2]);
}
BLYNK_WRITE(V0)
{
  schedule[0] = param.asInt();
  writeFile(SPIFFS, pathSchedule[0],  String(schedule[0]));
  secondtoHandM(schedule[0], jHour[0], jMinute[0]);
  Serial.print("Schedule = 0");
  Serial.print("Time in Second = ");
  Serial.println(schedule[0]);
  Serial.print("Hour = ");
  Serial.println(jHour[0]);
  Serial.print("Minute = ");
  Serial.println(jMinute[0]);
}
BLYNK_WRITE(V1)
{
  schedule[1] = param.asInt();
  writeFile(SPIFFS, pathSchedule[1],  String(schedule[1]));
  secondtoHandM(schedule[1], jHour[1], jMinute[1]);
  Serial.print("Schedule = 1");
  Serial.print("Time in Second = ");
  Serial.println(schedule[1]);
  Serial.print("Hour = ");
  Serial.println(jHour[1]);
  Serial.print("Minute = ");
  Serial.println(jMinute[1]);
}
BLYNK_WRITE(V2)
{
  schedule[2] = param.asInt();
  writeFile(SPIFFS, pathSchedule[2],  String(schedule[2]));
  secondtoHandM(schedule[2], jHour[2], jMinute[2]);
  Serial.print("Schedule = 2");
  Serial.print("Time in Second = ");
  Serial.println(schedule[2]);
  Serial.print("Hour = ");
  Serial.println(jHour[2]);
  Serial.print("Minute = ");
  Serial.println(jMinute[2]);
}
//void myTimerEvent()
//{
//  Blynk.virtualWrite(V6, VoulmePersen);
//}
void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  Blynk.begin(auth, ssid, pass);
//  timer.setInterval(10000L, myTimerEvent);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  servo.setPeriodHertz(50);// Standard 50hz servo

  getDatafromFile();
  scale.begin(DOUT, CLK);
  scale.set_scale();
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
  delay(1000);
  sizeArray = sizeof(jHour) / sizeof(jHour[0]);
  Serial.print("size Array =");
  Serial.println(sizeArray);
}
unsigned long  prevPrint;
unsigned long prevSendVolume;
void loop() {
//  timer.run();
  Blynk.run();
  SerialTest();
  if ( year() == 1970 )
  {
    ntpBegin();
  }
  String timeNow = getFulldate();
  //  if ( millis() - prevPrint >= 1000)
  //  {
  //    Serial.print("Time Now = ");
  //    Serial.println(timeNow);
  //    Serial.print("gram now = ");
  //    Serial.println(readGram());
  //    prevPrint = millis();
  //  }
  if ( millis() - prevSendVolume >= 10000)
  {
    Volume = readVolume();
    VoulmePersen = mapfloat(Volume, MinVolume, MaxVolume);
    Serial.print("Volume Persen = ");
    Serial.println(VoulmePersen);
    Blynk.virtualWrite(V6, VoulmePersen);
    prevSendVolume = millis();
    
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
