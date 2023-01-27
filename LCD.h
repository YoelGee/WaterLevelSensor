#ifndef LCD_H_
#define LCD_H_
#include "LiquidCrystal.h" 

#define valves 4
#define pointer 2


class LCD{
    private:

        LiquidCrystal lcd;

    public:

       void startLCD();

       void updateLCD(float temp, int waterLVL);

       LCD();

};

#endif