#include "MainRotary.h"
#include <Arduino.h>
#include "SketchPins.h"
#include "SketchConstants.h"

Push rotaryPush = Push(pins.rotaryPush, INPUT_PULLUP, rotary_push_debounce);
RotaryDecoder rotary = RotaryDecoder(pins.rotaryA, pins.rotaryB, INPUT_PULLUP);
Gradational rotaryGradational = Gradational();
void (*rotaryTurnedCallback)(byte) = nullptr;

void rotaryISR()
{
    byte state = rotary.decode();

    if (state == CCW)
    {
        if (rotaryTurnedCallback)
            rotaryTurnedCallback(state);
        rotaryGradational.gradate(DECREMENT);
    }
    else if (state == CW)
    {
        if (rotaryTurnedCallback)
            rotaryTurnedCallback(state);
        rotaryGradational.gradate(INCREMENT);
    }
}

void mainRotarySetup()
{
    attachInterrupt(digitalPinToInterrupt(pins.rotaryA), rotaryISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pins.rotaryB), rotaryISR, CHANGE);
}