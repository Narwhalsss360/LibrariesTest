#ifndef SketchConstants_h
#define SketchConstants_h

#include <stdint.h>
#include <TimeTypes.h>
#include <TimeLiterals.h>

constexpr uint8_t display_address = 0x27;
constexpr ntime_t::int_type display_refresh_rate = 15_hz;
constexpr uint8_t display_rows = 4;
constexpr uint8_t display_columns = 20;

constexpr uint16_t rotary_push_debounce = 20;

constexpr uint16_t ultrasonic_ping_interval = 80;
#endif