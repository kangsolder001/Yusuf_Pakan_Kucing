void SerialTest()
{
  if (Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    if ( in == "feed")
    {
      feed(1000);
    }
  }
}
