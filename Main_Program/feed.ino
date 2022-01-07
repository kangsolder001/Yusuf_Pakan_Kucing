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
