#include "waterLVL.h"
#include "tempSens.h"
#include "MAX6675.h"

int LiquidLVL = 0;

File file;
SdFat sd;

tempSensor temp;
waterSensor water;

// MAX6675 ktc;

float tempCelcius;
float tempFahrenheit;
//String

MAX6675 ktc;
//thermoCouple.begin(CLK_PIN, CS_PIN, SO_PIN);

void setup() {
  // put your setup code here, to run once:
  pinMode(SENSOR,INPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  Serial.begin(9600);
  delay(500);
  temp.initializesd();
  ktc.begin(CLK_PIN, CS_PIN, SO_PIN);
  ktc.setSPIspeed(4000000);
}

void loop() {

  tempFahrenheit = ktc.getTemperature();
  tempCelcius = (tempFahrenheit-32)*(5/9);
   //tempCelcius = thermoCouple.getTemperature;
   temp.editFileLog(String(tempCelcius), LiquidLVL, temp.filenameGetter()); //write to the file 
   Serial.print("Deg C = ");
   Serial.print(tempCelcius);
   Serial.print("\t Deg F = ");
   Serial.println(tempFahrenheit);
 
  delay(500);
  // put your main code here, to run repeatedly:
  LiquidLVL = digitalRead(SENSOR);
  if(LiquidLVL == 0){
    digitalWrite(BUZZER, LOW);
    Serial.println("Water Level is Low");
    delay(250);
  }
  else if (LiquidLVL == 1){
    digitalWrite(BUZZER, HIGH);
    Serial.println("Water Level is Good");
    delay(250);
  }

}
