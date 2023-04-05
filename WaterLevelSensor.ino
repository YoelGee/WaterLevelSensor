#include "Arduino.h"
#include "waterLVL.h"
#include "tempSens.h"
//#include "MAX6675.h"
#include "max6675.h"
#include "SDcard.h"
//#include "LCD.h"
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library


#define CS_PIN 53
#define CLK_PIN 52
#define SO_PIN 50

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int LiquidLVL = 0;
bool emailSent = false;

int ktcSO = 50;
int ktcCS = 53;
int ktcCLK = 52;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);
//SDcard data;
//LCD lcd;
bool initialize = false;
int waterlvl[5] = {2,2,2,2,2};
int i=0;
bool wLVL;
float tempCelcius;
float tempFahrenheit;

LCDWIKI_KBV mylcd(ILI9486,A3,A2,A1,A0,A4);


void updateLCD(float temp, int waterLVL){
  mylcd.Set_Text_Mode(0);
  //mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("Temp in C:", 0, 54);
  mylcd.Print_Number_Float(temp, 2, 0, 114, '.', 0, ' ');  
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Print_String("Water LEVEL:", 0, 208);
  if(waterLVL == 1){
  mylcd.Print_String("HIGH", 0, 268);
  }
  else 
   mylcd.Print_String("LOW", 0, 268);

   mylcd.Set_Text_colour(GREEN);
   mylcd.Print_String("STATUS:", 0, 362);
   if(temp >= 80){
    mylcd.Print_String("HOT", 0, 422);
   }
   else
    mylcd.Print_String("STABLE", 0, 422);
}





void setup() {
  // put your setup code here, to run once:
   mylcd.Init_LCD();
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
    //updateLCD(tempCelcius, 1);
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
    //updateLCD(tempCelcius, 0);
    digitalWrite(BUZZER, HIGH);
    Serial.println("Water Level is Low");
    //data.editFileLog(String(tempCelcius), 0);
    delay(250);
  }

  mylcd.Set_Text_Mode(0);
  //mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_colour(RED);
  mylcd.Set_Text_Size(4);
  mylcd.Print_String("Temp in C:", 0, 54);
  mylcd.Print_Number_Float(tempCelcius, 2, 0, 114, '.', 0, ' ');  
  mylcd.Set_Text_colour(YELLOW);
  mylcd.Print_String("Water LEVEL:", 0, 208);
  if(wLVL == 1){
  mylcd.Print_String("HIGH", 0, 268);
  }
  else 
   mylcd.Print_String("LOW", 0, 268);

   mylcd.Set_Text_colour(GREEN);
   mylcd.Print_String("STATUS:", 0, 362);
   if(tempCelcius >= 80){
    mylcd.Print_String("HOT", 0, 422);
   }
   else
    mylcd.Print_String("STABLE", 0, 422);
  
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