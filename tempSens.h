#ifndef __TEMPSENS_H_
#define __TEMPSENS_H_

#include <SPI.h>
#include "SdFat.h"

#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
// Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif  // SDCARD_SS_PIN

// Try max SPI clock for an SD. Reduce SPI_CLOCK if errors occur.
#define SPI_CLOCK SD_SCK_MHZ(50)

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif  ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else  // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif  // HAS_SDIO_CLASS

#define error(s) sd.errorHalt(&Serial, F(s))

#define CS_PIN 53
#define CLK_PIN 52
#define SO_PIN 50
//

// File accessedFile;
// SdFat accessedSd;


class tempSensor{
    private:
        //SdFat SD;
        //File file;
        float temp;
        String filename;
    
    public:
        void tempSetter(int newTemp);
        void tempGetter();
        String readLine();
        int editFileLog(String tempC, int waterLVL);
        void filenameSetter(String fname);
        void initializeSD();
        String filenameGetter();
};

#endif