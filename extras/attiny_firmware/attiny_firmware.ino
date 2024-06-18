/**
 **************************************************
 *
 * @file        Template for attiny_firmware
 * @brief       Fill in sensor specific code.
 *
 *
 * @note        To compile this code, you'll need to have ShiftRegister74HC595 library installed

 *
 * @authors     robert @ soldered.com
 ***************************************************/

#include "easyC.h"
#include <ShiftRegister74HC595.h>
#include <Wire.h>

// Pin constants
const int brightnessPwmPin = PA5;
const int shiftDataPin = PA1;
const int shiftClockPin = PA3;
const int shiftLatchPin = PA4;

ShiftRegister74HC595<1> sr(shiftDataPin, shiftClockPin, shiftLatchPin);

int addr = DEFAULT_ADDRESS;

uint8_t pinValues[] = {B11111111};
uint8_t brightness = 255; // Start at full brightness

void setup()
{
    initDefault();
    addr = getI2CAddress();

    Wire.begin(addr);
    Wire.onReceive(receiveEvent);

    sr.setAll(pinValues);
    pinMode(brightnessPwmPin, OUTPUT);
    analogWrite(brightnessPwmPin, brightness);
}

void loop()
{
}


void receiveEvent(int howMany)
{
    if (howMany == 2)
    {
        // 2 bytes will be recieved, pin state and brightness
        uint8_t _pins = Wire.read();
        uint8_t _brightness = Wire.read();
        pinValues[0] = _pins;
        brightness = _brightness;
        sr.setAll(pinValues);
        analogWrite(brightnessPwmPin, brightness);
    }
}
