#ifndef SketchPins_h
#define SketchPins_h

#include <stdint.h>

const constexpr struct SketchPins
{
    const uint8_t
        rotaryA = 3,
        rotaryB = 2,
        rotaryPush = 4,
        ledRed = 9,
        ledGreen = 6,
        ledBlue = 5,
        ultrasonicTrigger = 7,
        ultrasonicEcho = 8;
} pins;

#endif