#include "LCD.h"

 LCD::LCD(): mylcd(ILI9486,A3,A2,A1,A0,A4){
 }


void LCD::updateLCD(float temp, int waterLVL){
  //Serial.println("Inside method");
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_Mode(0);
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

void LCD::InitializeLCD(){
    mylcd.Init_LCD();
}

void LCD::StartUpLCD(){
    mylcd.Fill_Screen(0x0000);
    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_colour(YELLOW);
    mylcd.Set_Text_Size(4);
    mylcd.Print_String("Water LEVEL", 0, 208);
    mylcd.Print_String("initializing", 0, 268);
    mylcd.Print_String("PLEASE WAIT...", 0, 328);
}


