/**
 **************************************************
 *
 * @file        sevenSegment.ino
 * @brief       Example for 7-segment display breakout with easyC.
 *
 *              For this example you will need any Dasduino board, a USB-C cable, 7-segment display breakout, and easyC
 *cable. Don't have Dasduino? Get it here: https://soldered.com/categories/dasduino-arduino/dasduino-boards/ Don't have
 *easyC cable? Get it here: https://soldered.com/categories/easyc-2/easyc-cables-adapters/
 *
 *              This example will show you how to simply display numbers and characters and custom characters
 *              with variable brightness
 *
 * @link        solde.red/333190, solde.red/333206, solde.red/333207
 *
 * @authors     robert @ soldered.com
 ***************************************************/

// Include the library
#include "7-segment-display-easyC-SOLDERED.h"

// Create the object on the library
SevenSegment sevenSegment;

// Let's create a custom character to display
// S like Soldered!
// '0' means segment is ON, '1' means it's off
uint8_t customChar = 0b01001001;

// Setup code, runs only once
void setup()
{
    // Initialize the breakout
    sevenSegment.begin();
    // If you want another I2C address, enter it in the bracket
    // You can set another I2C address (0x31 - 0x37) by changing address switches on the breakout
    // NOTE: You have to restart breakout to apply the address change
    // eg. sevenSegment.begin(0x31);
}

// This part of the code, the demonstration, runs repeteadly
void loop()
{
    // Display numbers 0 to 9 with 100ms delay between each
    for (uint8_t num = 0; num <= 9; num++)
    {
        sevenSegment.displayNumber(num);
        delay(350);
    }
    delay(1000); // Wait a bit

    // Display characters A, B, C, D, E, F with 100ms delay between each
    char chars[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    for (int i = 0; i < 6; i++)
    {
        sevenSegment.displayChar(&chars[i]);
        delay(350);
    }
    delay(1000); // Wait a bit

    // Randomize pins 10 times with 50ms delay
    for (int i = 0; i < 10; i++)
    {
        uint8_t randomPins = random(0, 256); // Random value between 0 and 255
        sevenSegment.setPins(randomPins);
        delay(75);
    }

    delay(1000); // Wait a bit

    // Turn all the pins on
    sevenSegment.setPins(0b00000000);
    // Fade brightness from 0 to 255
    for (uint8_t brightness = 0; brightness <= 128; brightness += 16)
    {
        sevenSegment.setBrightness(brightness);
        delay(100);
    }
    delay(1000); // Wait a bit

    // Many chars are supported! But they are approximated on the limited 7-segment display
    char soldered[] = {'S', 'O', 'L', 'D', 'E', 'R', 'E', 'D'};
    for (int i = 0; i < 8; i++)
    {
        sevenSegment.displayChar(&soldered[i]);
        delay(350);
    }
    delay(1000); // Wait a bit
}