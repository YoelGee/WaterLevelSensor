#ifndef LCD_H_
#define LCD_H_
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

class LCD{
    private:
            LCDWIKI_KBV mylcd;
    public:
        void InitializeLCD();
       void updateLCD(float temp, int waterLVL);

       LCD();

};

#endif