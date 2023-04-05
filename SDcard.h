#ifndef __SDCARD_H_
#define __SDCARD_H_

#include <SPI.h>
#include "SdFat.h"




// Try to select the best SD card configuration.

#define error(s) sd.errorHalt(&Serial, F(s))
#define SPI_SPEED SD_SCK_MHZ(4)
#define CS_PIN 53
#define CLK_PIN 52
#define SO_PIN 50
//

// File accessedFile;
// SdFat accessedSd;


class SDcard{
    private:
        SdFat sd;
        //File file;
        float temp;
        String filename;
    
    public:

        String readLine();
        int editFileLog(String tempC, int waterLVL);
        void filenameSetter(String fname);
        void initializeSD();
        String filenameGetter();


};

#endif

