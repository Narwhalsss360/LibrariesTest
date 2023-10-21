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

const byte rowPins[] = { 10, 11 };
const byte columnPins[] = { 12, A0, A1 };
auto matrix = createMatrix(rowPins, columnPins, 10);
BitArray<static_array_length(byte, rowPins)> statesRows[static_array_length(byte, columnPins)];

template <size_t BitCount>
String stringifyBitArray(const BitArray<BitCount>& bits)
{
    String result = "[";
    for (size_t i = 0; i < BitCount; i++)
    {
        result += String(bits.get(i));
        if (i != BitCount - 1)
            result += ", ";
    }
    result += ']';
    return result;
}

void showMatrixStates()
{
    Serial.println("Matrix States:");
    for (size_t i = 0; i < static_array_length(byte, rowPins); i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(stringifyBitArray(statesRows[i]));
    }
}

void rotaryPushed(PushedEventArgs&)
{
    lines[2] = "Rotary Pushed";
    showMatrixStates();
}

void rotaryReleased(ReleasedEventArgs args)
{
    lines[2] = "Rotary released, held for " + String((uint32_t)args.holdTime);
}

void incrementColor(ElapsedEventArgs&)
{
    ledCol.hue = (ledCol.hue != 360 ? ledCol.hue + 5 : 0);
    led.setColor(ledCol, 64);
}

void matrixUpdate(byte row, byte column, bool state)
{
    statesRows[row].set(column, state);
    lines[2] = "R" + String(row) + "C" + String(column) + " was set as: " + String(state);
}

void setup()
{
    ledCol.saturation = 100;
    ledCol.value = 100;

    ledColorChanger.elapsed += incrementColor;
    ledColorChanger.start();

    testStart();
    testEnd();
    Serial.begin(115200);

    ultrasonicSetup();

    displaySetup();

    mainRotarySetup();
    rotaryGradational.set<uint16_t>(&ultrasonic.maxCentimeters, 10, 400, 5, I_U16, true);
    rotaryPush.push += rotaryPushed;

    matrix.updateHandler += matrixUpdate;
}

time_t lastLoopTime;
void loop()
{
    time_t start = uptime();

    lines[0] = fromRight("cm", String(ultrasonic.centimeters(false)), display_columns);
    lines[1] = fromRight("Max cm", String(ultrasonic.maxCentimeters), display_columns);
    lastLoopTime = uptime() - start;
}

DynamicArray<uint8_t> readAll(Stream& stream)
{
    DynamicArray<uint8_t> readBytes;
    while (stream.available())
    {
        int read = stream.read();
        if (read)
            readBytes += read;
    }
    return readBytes;
}

void serialEvent()
{
    DynamicArray<uint8_t> bytes = readAll(Serial);
    Serial.write(&bytes[0], bytes.Length());
    Serial.println();
}