#include "SDcard.h"
//e
char line[40];

void SDcard::initializeSD()
{
  Serial.print("Hi");
  if (!sd.begin(CS_PIN, SPI_SPEED)) {
    sd.initErrorHalt(&Serial);
    Serial.print("initializing");
    return;
  }
}  

void SDcard::rtcInit(){
  Serial.println("In rtc");
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  Serial.println("End of rtc func");
}


int SDcard::editFileLog(String tempC, int waterLVL) {
  File file;
  if (!file.open("WeatherBox.csv" , FILE_WRITE)) {
    error("open failed");
  }
  
  // Get the current date and time from the RTC module
  DateTime now = rtc.now();

  // Write the current date to the file
  file.print(now.year(), DEC);
  file.print('/');
  if (now.month() < 10) {
    file.print('0');
  }
  file.print(now.month(), DEC);
  file.print('/');
  if (now.day() < 10) {
    file.print('0');
  }
  file.print(now.day(), DEC);
  file.print(',');

  // Write the current time to the file
  if (now.hour() < 10) {
    file.print('0');
  }
  file.print(now.hour(), DEC);
  file.print(':');
  if (now.minute() < 10) {
    file.print('0');
  }
  file.print(now.minute(), DEC);
  file.print(':');
  if (now.second() < 10) {
    file.print('0');
  }
  file.print(now.second(), DEC);
  file.print(',');

  // Write the temperature to the file
  file.print(tempC);
  file.print(',');

  // Write the water level to the file
  if(waterLVL == 1) {
    file.print(F("Water Level is stable."));
  }
  else if(waterLVL == 0) {
    file.print(F("Water Level is low."));
  }

  // Write a new line character and close the file
  file.println();
  file.close();
}




