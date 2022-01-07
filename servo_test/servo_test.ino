#include<ESP32Servo.h>
Servo servo;
void setup() {
  Serial.begin(115200);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  // put your setup code here, to run once:

  servo.setPeriodHertz(50);// Standard 50hz servo


}

void loop() {
  if ( Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    int pos = in.toInt();
    servo.attach(4);
    servo.write(pos);
    delay(500);
    servo.detach();

  }
  // put your main code here, to run repeatedly:

}
