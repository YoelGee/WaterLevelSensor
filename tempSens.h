#ifndef __TEMPSENS_H_
#define __TEMPSENS_H_

#include <SPI.h>
#include "SdFat.h"

#define CS_PIN 53
#define CLK_PIN 52
#define SO_PIN 8

// File accessedFile;
// SdFat accessedSd;


class tempSensor{
    private:
        float temp;
        String filename;
    
    public:
        void tempSetter(int newTemp);
        void tempGetter();
        String readLine();
        int editFileLog(String tempC, int waterLVL, String filename);
        void filenameSetter(String fname);
        void initializesd();
        String filenameGetter();
};

#endif