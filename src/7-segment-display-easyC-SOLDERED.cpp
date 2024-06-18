/**
 **************************************************
 *
 * @file        7-segment-display-easyC-SOLDERED.cpp
 * @brief       Function for the 7-segment display with easyC
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     robert @ soldered.com
 ***************************************************/

#include "7-segment-display-easyC-SOLDERED.h"

/**
 * @brief Construct a new Seven Segment:: Seven Segment object
 *
 */
SevenSegment::SevenSegment()
{
    native = 0; // Not native, easyC only!
}

/**
 * @brief Overloaded from base function
 *
 */
void SevenSegment::initializeNative()
{
}

/**
 * @brief Set the pins of the 7segment display. In the byte, 0 is a segment turned on, 1 is a segment turned off.
 *
 *  Segment mapping:
 *   --a--
 *  |     |
 *  f     b
 *  |     |
 *   --g--
 *  |     |
 *  e     c
 *  |     |
 *   --d--   dot (dp)
 *
 * The byte is constructed as follows:
 * Bit 7  - dot (dp)
 * Bit 6  - segment a
 * Bit 5  - segment b
 * Bit 4  - segment c
 * Bit 3  - segment d
 * Bit 2  - segment e
 * Bit 1  - segment f
 * Bit 0  - segment g
 *
 * @param _pins the state of the pins, as described in the comment above
 */
void SevenSegment::setPins(uint8_t _pins)
{
    // Save the recieved pins
    currentPins = _pins;

    // Send the data to display along with the saved brightness
    uint8_t dataToSend[2] = {currentPins, brightness};
    sendData(dataToSend, 2);
}

/**
 * @brief Set the brightness of the 7 segment display
 *
 * @param _brightness, values from 0 to 127 will affect the display
 */
void SevenSegment::setBrightness(uint8_t _brightness)
{
    // Save the recieved brightness
    brightness = _brightness;

    // Send the data to the board
    uint8_t dataToSend[2] = {currentPins, brightness};
    sendData(dataToSend, 2);
}

/**
 * @brief Show a capital char on the seven segment display
 *
 * @note This function accepts large capital letter chars
 *
 * @param _char the character to display
 */
void SevenSegment::displayChar(char *_char)
{
    uint8_t data = 0b11111111;
    switch (*_char)
    {
    case 'A':
        data = 0b10001000; // Inverted: Segments: a, b, c, e, f, g
        break;
    case 'B':
        data = 0b10000000; // Inverted: Segments: a, b, c, d, e, f, g
        break;
    case 'C':
        data = 0b11000110; // Inverted: Segments: a, d, e, f
        break;
    case 'D':
        data = 0b11000000; // Inverted: Segments: a, b, c, d, e, f
        break;
    case 'E':
        data = 0b10000110; // Inverted: Segments: a, d, e, f, g
        break;
    case 'F':
        data = 0b10001110; // Inverted: Segments: a, e, f, g
        break;
    case 'G':
        data = 0b11000010; // Inverted: Segments: a, c, d, e, f
        break;
    case 'H':
        data = 0b10001001; // Inverted: Segments: b, c, e, f, g
        break;
    case 'I':
        data = 0b11001111; // Inverted: Segments: e, f
        break;
    case 'J':
        data = 0b11100001; // Inverted: Segments: b, c, d, e
        break;
    case 'K':
        data = 0b10001001; // Inverted: Segments: a, b, d, e, f, g (approximated as H)
        break;
    case 'L':
        data = 0b11000111; // Inverted: Segments: d, e, f
        break;
    case 'M':
        data = 0b11101010; // Inverted: Segments: a, c, e, f (approximated)
        break;
    case 'N':
        data = 0b11001000; // Inverted: Segments: a, b, c, e, f (approximated)
        break;
    case 'O':
        data = 0b11000000; // Inverted: Segments: a, b, c, d, e, f
        break;
    case 'P':
        data = 0b10001100; // Inverted: Segments: a, b, e, f, g
        break;
    case 'Q':
        data = 0b10011000; // Inverted: Segments: a, b, c, e, f, g
        break;
    case 'R':
        data = 0b11001110; // Inverted: Segments: a, b, c, f, g
        break;
    case 'S':
        data = 0b10010010; // Inverted: Segments: a, b, d, f, g
        break;
    case 'T':
        data = 0b10000111; // Inverted: Segments: d, e, f, g
        break;
    case 'U':
        data = 0b11000001; // Inverted: Segments: b, c, d, e, f
        break;
    case 'V':
        data = 0b11000001; // Inverted: Segments: b, c, d, e, f (same as U)
        break;
    case 'W':
        data = 0b11010101; // Inverted: Segments: b, d, f, g (approximated)
        break;
    case 'X':
        data = 0b10001001; // Inverted: Segments: a, b, d, e, f, g (approximated as H)
        break;
    case 'Y':
        data = 0b10010001; // Inverted: Segments: a, b, c, d, f, g (approximated)
        break;
    case 'Z':
        data = 0b10100100; // Inverted: Segments: a, b, c, d, e, g
        break;
    default:
        data = 0b11111111; // Turn off all segments for any other character
        break;
    }

    currentPins = data;
    uint8_t dataToSend[2] = {currentPins, brightness};
    sendData(dataToSend, 2);
}

/**
 * @brief Show a number on the 7 segment display
 *
 * @param _num The nubmer to show, single digits numbers are accepted only
 */
void SevenSegment::displayNumber(uint8_t _num)
{
    uint8_t data = 0b11111111; // Turn off all segments initially

    switch (_num)
    {
    case 0:
        data = 0b11000000; // Segments: a, b, c, e, f, g
        break;
    case 1:
        data = 0b11111001; // Segments: c, f
        break;
    case 2:
        data = 0b10100100; // Segments: a, c, d, e, g
        break;
    case 3:
        data = 0b10110000; // Segments: a, c, d, f, g
        break;
    case 4:
        data = 0b10011001; // Segments: b, c, f, g
        break;
    case 5:
        data = 0b10010010; // Segments: a, b, d, f, g
        break;
    case 6:
        data = 0b10000010; // Segments: a, b, d, e, f, g
        break;
    case 7:
        data = 0b11111000; // Segments: a, c, f
        break;
    case 8:
        data = 0b10000000; // Segments: all segments on
        break;
    case 9:
        data = 0b10010000; // Segments: a, b, c, d, f, g
        break;
    default:
        data = 0b00000000; // Turn off all segments for invalid number
        break;
    }

    currentPins = data;
    uint8_t dataToSend[2] = {currentPins, brightness};
    sendData(dataToSend, 2);
}
