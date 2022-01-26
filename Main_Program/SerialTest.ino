void SerialTest()
{
  if (Serial.available())
  {
    String in = Serial.readStringUntil('\r');
    if ( in == "feed")
    {
      feed(1000);
    }
    else if ( in == "read")
    {
      getDatafromFile();
    }
    else
    {
      int a = in.toInt();
      Serial.println(mapfloat(a, MinVolume, MaxVolume));
    }
  }
}
