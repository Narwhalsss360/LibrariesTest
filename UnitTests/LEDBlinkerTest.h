#include <NTimer.h>

#define TOGGLE_LED() digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN))

TimedEvent ledBlinkEvent;

void toggleLED(ElapsedEventArgs&)
{
    TOGGLE_LED();
}

void testToggleLEDStart()
{
    pinMode(LED_BUILTIN, OUTPUT);
    ledBlinkEvent.interval = 500;
    ledBlinkEvent.autoReset = true;
    ledBlinkEvent.elapsed += toggleLED;
    ledBlinkEvent.start();
}