#include "SDcard.h"

char line[40];

void SDcard::initializeSD()
{
  if (!sd.begin(CS_PIN, SPI_SPEED)) {
    sd.initErrorHalt(&Serial);
    return;
  }

}  


int SDcard::editFileLog(String tempC, int waterLVL)
{
  File file;
  if (!file.open("WeatherBox.txt", FILE_WRITE)) {
    error("open failed");
  }
  // Write test data.
  file.print(F("Temperature (celcius) = "));
  file.print(tempC);
  if(waterLVL==1){
    file.print(F("\nWater Level is stable"));
  }
  else if(waterLVL == 0){
    file.print(F("Water Level is low"));
  }

  //accessedFile = accessedSd.open(filename, FILE_WRITE);
}


