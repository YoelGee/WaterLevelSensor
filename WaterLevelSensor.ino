#include "Arduino.h"
#include "waterLVL.h"
#include "tempSens.h"
//#include "MAX6675.h"
#include "max6675.h"
#include "SDcard.h"
#include "LCD.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library
#include "RTClib.h" 


int LiquidLVL = 0;
bool emailSent = false;

int ktcSO = 37;
int ktcCS = 53;
int ktcCLK = 33;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
//SDcard data;
LCD lcd{};
RTC_DS3231 rtc;
bool initialize = false;
int waterlvl[5] = {2,2,2,2,2};
int i=0;
bool wLVL;
float tempCelcius;
float tempFahrenheit;
long unsigned int current_time;

String data;
DateTime targetTime;

void setup() {

  pinMode(SENSOR,INPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  lcd.InitializeLCD();
  lcd.StartUpLCD();
  Serial.println("After LCD");
  Serial.println("Afte RTC");
  Serial.print("init");
  rtc.begin();// initialize rtc
  DateTime now = rtc.now();
  targetTime = now + TimeSpan(0, 2, 0, 0); //2 hours from current time

  //Serial2.print("SendEmail\n");
  delay(500);
}

void loop() {
  DateTime now = rtc.now();
  data = parseDate(); //adding current time/date to the data

  tempCelcius = ktc.readCelsius(); // setting up thermocouple
  data += tempCelcius; //adding temperature to the data
  tempFahrenheit = (tempCelcius*1.8) + 32;

  data += ", Water Level is ";

  i = checkWater(i);  // resets the array index for water initialization back to 0
  LiquidLVL = digitalRead(SENSOR); // reads current water level
  waterlvl[i] = LiquidLVL;  // water initialization array
  wLvLChecker(waterlvl); //checks if water has been initialized
  i++;

  delay(300);

  if(wLVL){
    lcd.updateLCD(tempCelcius, LiquidLVL);
    data+="Stable";
    initialize = true;
    Serial.println("Water Level is Good");
    delay(250);
  }

  if(!wLVL)
  {
    data+= "Low"; // adds water level to data
    lcd.updateLCD(tempCelcius, 0);
    delay(250);
  }

  if(initialize){ //if water initialization is complete send data that we want to record
    Serial1.print(data);

    if(now > targetTime) { //sends an indication to the ESP to send an email every 2 hours
    Serial1.print("SendEmail\n");
    targetTime =  now + TimeSpan(0, 2, 0, 0); //resets 2 hour interval
    }
 
  }
}

void wLvLChecker(int waterlvl[5]){
  for (int k = 0; k < 5; k++){
    if(waterlvl[k] != 1){
        wLVL = false;
        Serial.print("false");
        return;
    }
    else {
      wLVL = true;
      Serial.print("true");
    }
  }
}

String parseDate(){
  DateTime now = rtc.now();
  String new_data;
  new_data = now.year();
  new_data += "/";
  new_data += now.month();
  new_data += "/";
  new_data += now.day();
  new_data += " ";
  new_data += now.hour();
  new_data += ":";
  new_data += now.minute();
  new_data += ":";
  new_data += now.second();
  new_data += " , Temperature C = ,";
  return new_data;
}

int checkWater(int i) {
  if(i==5){
    return 0;
  }
}