#include "Display.h"
#include <NTimer.h>
#include <LiquidCrystal_I2C.h>

using stdcol::array;

LiquidCrystal_I2C display = LiquidCrystal_I2C(display_address, display_columns, display_rows);

TimedEvent displaySendEvent;

array<String, display_rows> lines = array<String, display_rows>();
array<String, display_rows> oldLines = array<String, display_rows>();

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

    for (int i = 0; i < display_rows; i++)
    {
        if (oldLines[i] == lines[i])
            continue;
        
        display.setCursor(0, i);
        display.print(lines[i]);

        String whitespaces;
        for (uint8_t i = 0; i < lines[i].length() - oldLines[i].length(); i++)
            whitespaces += ' ';

        if (whitespaces.length())
            display.print(whitespaces);

        oldLines[i] = lines[i];
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