void secondtoHandM(uint32_t Second, int &H, int&M)
{
  H = Second / 3600;
  int mod = Second % 3600;
  M = mod / 60;
}

void getDatafromFile()
{
  for ( int i = 0; i <= 2; i++)
  {
    String in;
    readFile(SPIFFS, pathSchedule[i], in);
    uint32_t timeInput = (uint32_t)strtol(in.c_str(), NULL, 0);
    secondtoHandM(timeInput, jHour[i], jMinute[i]);
    readFile(SPIFFS, pathPortion[i],  in);
    int Portion = in.toInt();
    jPortion[i] = Portion;
  }
}
