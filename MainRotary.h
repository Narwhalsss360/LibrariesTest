#ifndef MainRotary_h
#define MainRotary_h

#include <NRotary.h>
#include <NPush.h>

extern Push rotaryPush;
extern RotaryDecoder rotary;
extern Gradational rotaryGradational;
extern void (*rotaryTurnedCallback)(byte);

void mainRotarySetup();

#endif