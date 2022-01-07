float readGram()
{
  float gram;
  scale.set_scale(calibration_factor);
  //  Serial.print("get average = ");
  //  Serial.print(scale.read_average(5));
  //  Serial.print(" get value = ");
  //  Serial.print(scale.get_value(5));
  gram = scale.get_units(5);
  return gram;
}

void moveServo( int degre)
{
  servo.attach(serPin);
  servo.write(degre);
  delay(500);
  servo.detach();
}

float readVolume()
{
  long duration;
  float distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
