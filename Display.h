#ifndef Display_h
#define Display_h

#include <Arduino.h>
#include "SketchConstants.h"
#include <stdcol.h>

extern stdcol::array<String, display_rows> lines;
extern uint8_t displayBrightness;

void displaySetup();

void customDisplayChar(uint8_t location, uint8_t map[]);

void sendFrame();

#endif