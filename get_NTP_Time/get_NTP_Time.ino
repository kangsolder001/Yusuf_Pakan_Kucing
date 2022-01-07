#include<WiFi.h>
#include<TimeLib.h>
#include <WiFiUdp.h>

const char* ssid = "Yusuf"; // IT-DEV
const char* password = "p3rbanas";
//==========================NTP====================================
static const char ntpServerName[] = "pool.ntp.org";
//IPAddress ntpServerIP(192, 168, 9, 20);
const int timeZone = 7;
WiFiUDP Udp;
unsigned int localPort = 8888;
time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void setup() {
  Serial.begin(115200);
  wifi();
  
  // put your setup code here, to run once:

}

void loop() {
  if ( year() == 1970 ) 
  {
    ntpBegin();
  }
  
  // put your main code here, to run repeatedly:

}
