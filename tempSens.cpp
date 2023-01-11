#include "tempSens.h"


void tempSensor::initializeSD()
{
  
  Serial.println("Initializing sd card...");
  //53, SPI_SPEED
  SdFat sd;
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

int tempSensor::editFileLog(String tempC, int waterLVL, String filename)
{

  //accessedFile = accessedSd.open(filename, FILE_WRITE);
  File file;
  SdFat sd;
  file = sd.open(filename, FILE_WRITE);
  if (file)
  {
    file.print("Temp at time: ");
    file.println(tempC);
    if(waterLVL == 1){
    file.println("WaterLVL is good");
    }
    else if(waterLVL == 0){
      file.println("WaterLVL is low");
    }
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
  File file;
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
