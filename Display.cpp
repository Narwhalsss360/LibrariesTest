#include "Display.h"
#include <NTimer.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C display = LiquidCrystal_I2C(display_address, display_columns, display_rows);

TimedEvent displaySendEvent;

Array<String, display_rows> lines = Array<String, display_rows>();
Array<String, display_rows> oldLines = Array<String, display_rows>();

uint8_t oldDisplayBrightness = 0;
uint8_t displayBrightness = 255;


void customDisplayChar(uint8_t location, uint8_t map[])
{
    display.createChar(location, map);
}

void sendFrame()
{
    if (displayBrightness != oldDisplayBrightness)
    {
        oldDisplayBrightness = displayBrightness;
        display.setBacklight(displayBrightness);
    }

    for (auto linesZip : Zip(oldLines, lines))
    {
        if (linesZip.value1 == linesZip.value2)
            continue;
        
        display.setCursor(0, linesZip.index);
        display.print(linesZip.value2);

        String whitespaces;
        for (uint8_t i = 0; i < linesZip.value2.length() - linesZip.value2.length(); i++)
            whitespaces += ' ';

        if (whitespaces.length())
            display.print(whitespaces);

        linesZip.value1  = linesZip.value2;
    }
}

inline void sendFrameWrapper(ElapsedEventArgs&) { sendFrame(); }

void displaySetup()
{
    display.init();
    displaySendEvent.interval = 1000 / display_refresh_rate;
    displaySendEvent.autoReset = true;
    displaySendEvent.elapsed += sendFrameWrapper;
    displaySendEvent.start();
}