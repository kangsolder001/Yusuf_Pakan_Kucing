#include "HX711.h"
#define DOUT  23
#define CLK  19
HX711 scale;
float calibration_factor = 334;
int GRAM;

void setup() {
  Serial.begin(115200);
  Serial.println("tekan a,s,d,f untuk menaikan calibration_factor ke 10,100,1000,10000");
  Serial.println("tekan z,x,c,v untuk menurunkan calibration_factor ke 10,100,1000,10000");
  Serial.println("Tekan T untuk Tare");
  scale.begin(DOUT,CLK);
  scale.set_scale();
//  scale.tare(5);
  long zero_factor = scale.read_average();
  Serial.print("Zero factor: ");
  Serial.println(zero_factor);
  delay(1000);
}

void loop() {
  
  scale.set_scale(calibration_factor);
  Serial.print("get average = ");
  Serial.print(scale.read_average(5));
  Serial.print(" get value = ");
  Serial.print(scale.get_value(5));
  GRAM = scale.get_units(5);
  Serial.print(", Reading: ");
  Serial.print(GRAM);
  Serial.print(" Gram");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if (Serial.available()) {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 0.1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 0.1;
    else if (temp == 's')
      calibration_factor += 10;
    else if (temp == 'x')
      calibration_factor -= 10;
    else if (temp == 'd')
      calibration_factor += 100;
    else if (temp == 'c')
      calibration_factor -= 100;
    else if (temp == 'f')
      calibration_factor += 1000;
    else if (temp == 'v')
      calibration_factor -= 1000;
    else if (temp == 't')
      scale.tare(5);
  }
}
