
void savetoSpiffs(String jsonData)
{
  String dataMem;
  readFile(SPIFFS, "/json.json", dataMem);
  delay(10);
//  dataMem = addJson(dataMem, jsonData);
  writeFile(SPIFFS, "/json.json", dataMem);
  Serial.println("Save to SPIFFS done");
}


void readFile(fs::FS &fs, const char * path, String &in) 
{
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }
  if (file.available()) {
    in = file.readStringUntil('\r');
  }
}

void writeFile(fs::FS &fs, const char * path, String message) 
{
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("Write Data");
  } else {
    Serial.println("Write NULL");
  }
}
