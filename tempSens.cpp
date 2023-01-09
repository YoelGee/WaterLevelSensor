#include "tempSens.h"


void tempSensor::initializesd(SdFat accessedSd)
{
  Serial.println("Initializing sd card...");
  pinMode(CS_PIN, OUTPUT);

  if (accessedSd.begin())
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


int tempSensor::editFileLog(String tempC, int waterLVL, String filename, 
File accessedFile, SdFat accessedSd)
{

  accessedFile = accessedSd.open(filename, FILE_WRITE);
  
  if (accessedFile)
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


String tempSensor::readLine(File accessedFile)
{
  String received = "";
  char ch;
  while (accessedFile.available())
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
