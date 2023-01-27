#include "lcd.h"
#include "LiquidCrystal.h" 
//check different values for each button

//Initialzes the LCD controll pins
LCD::LCD():lcd(8,9,4,5,6,7){
    lcd.begin(16,2);
    lcd.clear();
}


//Function used in main menu display, as well as within the cursor movement functions.
void LCD::startLCD(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ESS weather box");
    lcd.setCursor(0,1);
    lcd.print("initializing");
}



void LCD::updateLCD(float temp, int waterLVL){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp(C): ");
    lcd.setCursor(9,0);
    lcd.print(temp);
    lcd.setCursor(0,1);
    lcd.print("W lvl: ");
    lcd.setCursor(6,1);
    if(waterLVL == 1)
    lcd.print("Stable");
    else
    lcd.print("LOW");
}




