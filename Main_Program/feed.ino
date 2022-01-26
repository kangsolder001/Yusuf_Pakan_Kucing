void feed(unsigned int portion)
{
  moveServo(openServo);
  Serial.print("Open Servo");
  float feedGram;
  while ( feedGram <= portion)
  {
    feedGram = readGram();
    Serial.print("gram =");
    Serial.println(feedGram);
  }
  moveServo(closeServo);
  Serial.print("Close Servo");
}


unsigned int mapfloat(float x, float in_min, float in_max)
{
  int output =  (x - in_min) * (0 - 100) / (in_max - in_min) + 100;
  if ( output < 0)
  {
    output = 0;
  }
  else if ( output > 100)
  {
    output = 100;
  }
  return output;
}
