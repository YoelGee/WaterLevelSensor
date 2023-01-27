#include "tempSens.h"

char line[40];

void tempSensor::initializeSD()
{
  SdFat sd;
  File myFile;
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
    return;
  }

}  

String tempSensor::filenameGetter(){
    return filename;
}

void tempSensor::filenameSetter(String fname){
    filename = fname;
}

int tempSensor::editFileLog(String tempC, int waterLVL)
{
  SdFat sd;
  File file;
  if (!file.open("WeatherBox.txt", FILE_WRITE)) {
    error("open failed");
  }
  // Write test data.
  file.print(F("Temperature (celcius) = \n"));
  file.print(tempC);
  if(waterLVL==1){
    file.print(F("Water Level is stable"));
  }
  else if(waterLVL == 0){
    file.print(F("Water Level is low"));
  }

  //accessedFile = accessedSd.open(filename, FILE_WRITE);
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
