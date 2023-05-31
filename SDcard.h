// #ifndef __SDCARD_H_
// #define __SDCARD_H_

// #include <SPI.h>
// #include "SdFat.h"





// // Try to select the best SD card configuration.

// #define error(s) sd.errorHalt(&Serial, F(s))
// #define SPI_SPEED SD_SCK_MHZ(4)
// #define CS_PIN 38
// #define CLK_PIN 52
// #define SO_PIN 50
// //

// // File accessedFile;
// // SdFat accessedSd;


// class SDcard{
//     private:
//         int i =0;
//         SdFat sd;
//         RTC_DS3231 rtc;
//         float temp;
//         String filename;
    
//     public:

//         String readLine();
//         int editFileLog(String tempC, int waterLVL);
//         void filenameSetter(String fname);
//         void initializeSD();
//         String filenameGetter();
//         void rtcInit();


// };

// #endif

