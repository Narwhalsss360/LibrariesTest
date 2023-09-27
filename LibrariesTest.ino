#include <SketchBinder.h>
#include "SketchPins.h"
#include "LibraryIncludes.h"
#include "UnitTests.h"
#include "Display.h"
#include "MainRotary.h"
#include "Ultrasonic.h"

RGBLED led = RGBLED(pins.ledRed, pins.ledGreen, pins.ledBlue);
HSV ledCol;

TimedEvent ledColorChanger = TimedEvent(80, true);
BitArray<10> bitArr;

const byte rowPins[] = { 10, 11 };
const byte columnPins[] = { 12, A0, A1 };

auto matrix = createMatrix(rowPins, columnPins, 10);

void rotaryPushed(PushedEventArgs&)
{
}

void incrCol(ElapsedEventArgs&)
{
    ledCol.hue = (ledCol.hue != 360 ? ledCol.hue + 5 : 0);
    led.setColor(ledCol, 64);
}

void setup()
{
    ledCol.saturation = 100;
    ledCol.value = 100;

    ledColorChanger.elapsed += incrCol;
    ledColorChanger.start();

    testStart();
    testEnd();
    Serial.begin(115200);

    ultrasonicSetup();

    displaySetup();

    mainRotarySetup();
    rotaryGradational.set<uint16_t>(&ultrasonic.maxCentimeters, 10, 400, 5, I_U16, true);
    rotaryPush.push += rotaryPushed;
}

time_t lastLoopTime;
void loop()
{
    time_t start = uptime();

    lines[0] = fromRight("cm", String(ultrasonic.centimeters(false)), display_columns);
    lines[1] = fromRight("Max cm", String(ultrasonic.maxCentimeters), display_columns);
    lines[3] = fromRight("Loop Time", String((uint32_t)lastLoopTime), display_columns);
    lastLoopTime = uptime() - start;
}