#include "Arduino.h"
#include "waterLVL.h"
#include "tempSens.h"
//#include "MAX6675.h"
#include "max6675.h"
#include "SDcard.h"
#include "LCD.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library


#define CS_PIN 53
#define CLK_PIN 52
#define SO_PIN 50


int LiquidLVL = 0;
bool emailSent = false;

int ktcSO = 50;
int ktcCS = 53;
int ktcCLK = 52;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
//SDcard data;
LCD lcd;
bool initialize = false;
int waterlvl[5] = {2,2,2,2,2};
int i=0;
bool wLVL;
float tempCelcius;
float tempFahrenheit;



void setup() {
  // put your setup code here, to run once:
  lcd();
  pinMode(SENSOR,INPUT);
  Serial.begin(115200);
  Serial1.begin(115200);

  //data.initializeSD();
  //Serial2.print("SendEmail\n");
  delay(500);
}

void loop() {
  tempCelcius = ktc.readCelsius();
  tempFahrenheit = (tempCelcius*1.8) + 32;
  if(i==5){
    i=0;
  }
  LiquidLVL = digitalRead(SENSOR);
  waterlvl[i] = LiquidLVL;

  wLvLChecker(waterlvl);
  Serial.print("watrlvl ");
  Serial.println(i);
  Serial.println(waterlvl[i]);
  i++;
  delay(300);
  if(wLVL){
    lcd.updateLCD(tempCelcius, 1);
    initialize = true;
    digitalWrite(BUZZER, LOW);
    emailSent = false;
    Serial.println("Water Level is Good");
    //data.editFileLog(String(tempCelcius), 1);
    delay(250);
  }
  if(!wLVL & initialize == true) {
    if(!emailSent){
    Serial1.print("SendEmail\n");
    emailSent = true;
    initialize = false;
    }
    lcd.updateLCD(tempCelcius, 0);
    digitalWrite(BUZZER, HIGH);
    Serial.println("Water Level is Low");
    //data.editFileLog(String(tempCelcius), 0);
    delay(250);
  }


  
   //tempCelcius = thermoCouple.getTemperature;
 //write to the file 
   Serial.print("Deg C = ");
   Serial.print(tempCelcius);
   Serial.print("\t Deg F = ");
   Serial.println(tempFahrenheit);
 
  // put your main code here, to run repeatedly:
}

void wLvLChecker(int waterlvl[5]){
  for (int k = 0; k < 5; k++){
    if(waterlvl[k] != 1){
        wLVL = false;
        return;
    }
    else {
      wLVL = true;
    }
  }
}