#include "tempSens.h"


void tempSensor::initializesd(SdFat sd)
{
  Serial.println("Initializing sd card...");
  pinMode(CS_PIN, OUTPUT);

  if (sd.begin())
  {
    Serial.println("sd card is ready to use.");
  } else
  {
    Serial.println("sd card initialization failed");
    return;
  }
}  

String tempSensor::filenameGetter(){
    return filename;
}

void tempSensor::filenameSetter(String fname){
    filename = fname;
}


int tempSensor::editFileLog(String tempC, int waterLVL, String filename, File file, SdFat sd)
{

  file = sd.open(filename, FILE_WRITE);
  
  if (file)
  {
    file.println(tempC);
    file.println();
    Serial.println("Writing to file: ");
    Serial.println(tempC);
    delay(500);
    file.close();
    Serial.println("File closed");
  } 
  else
  {
    Serial.println("Error opening file...");
    return 0;
  }
}


String tempSensor::readLine()
{
  String received = "";
  char ch;
  while (file.available())
  {
    ch = file.read();
    if (ch == '\n')
    {
      return String(received);
    }
    else
    {
      received += ch;
    }
  }
  return "";
}
