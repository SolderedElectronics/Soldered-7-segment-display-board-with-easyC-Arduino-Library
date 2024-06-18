/**
 **************************************************
 *
 * @file        7-segment-display-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef __7SEGMENT_EASYC__
#define __7SEGMENT_EASYC__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

class SevenSegment : public EasyC
{
  public:
    SevenSegment();
    void setPins(uint8_t _pins);
    void setBrightness(uint8_t _brightness);
    void displayChar(char *_char);
    void displayNumber(uint8_t _num);

  protected:
    void initializeNative();

  private:
    int pin;
    uint8_t currentPins = 0b11111111; // Set initial state to all off
    uint8_t brightness = 128;         // Set max brightness for initial
};

#endif
