#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;
char auth[] = "ASeKdiRLR4DAZl64hYsZ7CBZOtFYQEKe";

char ssid[] = "NOMOREDOTAFORTOMMOROW";
char pass[] = "N0m0r3d0t4";
int p;
int portion[4];
int schedule[4];

int Volume;
BLYNK_WRITE(V3)
{
  portion[0] = param.asInt();
  Serial.print("Portion ");
  Serial.print("0");
  Serial.print(" : ");
  Serial.println(portion[0]);
}
BLYNK_WRITE(V4)
{
  portion[1] = param.asInt();
  Serial.print("Portion ");
  Serial.print("1");
  Serial.print(" : ");
  Serial.println(portion[1]);
}
BLYNK_WRITE(V5)
{
  portion[2] = param.asInt();
  Serial.print("Portion ");
  Serial.print("2");
  Serial.print(" : ");
  Serial.println(portion[2]);
}
BLYNK_WRITE(V0)
{
  
  schedule[0] = param.asInt();
  int jam;
  int menit;
  jam = schedule[0] / 3600;
  int mod = schedule[0] % 3600;
  menit = mod / 60;
  Serial.print("schedule ");
  Serial.print(0);
  Serial.print(" = ");
  Serial.println(schedule[0]);
  Serial.print("jam = ");
  Serial.println(jam);
  Serial.print("menit = ");
  Serial.println(menit);
}
BLYNK_WRITE(V1)
{
  schedule[1] = param.asInt();
  int jam;
  int menit;
  jam = schedule[1] / 3600;
  int mod = schedule[1] % 3600;
  menit = mod / 60;
  schedule[0] = param.asInt();
  Serial.print("schedule ");
  Serial.print(1);
  Serial.print(" = ");
  Serial.println(schedule[1]);
  Serial.print("jam = ");
  Serial.println(jam);
  Serial.print("menit = ");
  Serial.println(menit);
}
BLYNK_WRITE(V2)
{
  schedule[2] = param.asInt();
  int jam;
  int menit;
  jam = schedule[2] / 3600;
  int mod = schedule[2] % 3600;
  menit = mod / 60;
  schedule[0] = param.asInt();
  Serial.print("schedule ");
  Serial.print(2);
  Serial.print(" = ");
  Serial.println(schedule[2]);
  Serial.print("jam = ");
  Serial.println(jam);
  Serial.print("menit = ");
  Serial.println(menit);
}
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, Volume);
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  if (Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    Volume = in.toInt();
  }
  timer.run();
  
  //  if ( portion[0] != p )
  //  {
  //    p =  portion[0];
  //    for ( int i = 0; i <= 2; i++)
  //    {
  //      Serial.print("Portion ");
  //      Serial.print(i);
  //      Serial.print(" : ");
  //      Serial.println(portion[i]);
  //    }
  //    for ( int i = 0; i <= 2; i++)
  //    {
  //      int jam;
  //      int menit;
  //      jam = schedule[i] / 3600;
  //      int mod = schedule[i] % 3600;
  //      menit = mod / 60;
  //      Serial.print("schedule ");
  //      Serial.print(i);
  //      Serial.print(" = ");
  //      Serial.println(schedule[i]);
  //      Serial.print("jam = ");
  //      Serial.println(jam);
  //      Serial.print("menit = ");
  //      Serial.println(menit);
  //    }
  //  }
  Blynk.run();
}
