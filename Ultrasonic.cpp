#include "Ultrasonic.h"
#include "SketchPins.h"
#include "SketchConstants.h"
#include <NTimer.h>

TimedEvent pinger = TimedEvent(ultrasonic_ping_interval, true);

SR04 ultrasonic = SR04(pins.ultrasonicTrigger, pins.ultrasonicEcho, 25);

void ping(ElapsedEventArgs&)
{
    ultrasonic.ping();
}

void ultrasonicSetup()
{
    pinger.elapsed += ping;
    pinger.start();
}