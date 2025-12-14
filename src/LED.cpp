#include <Arduino.h>
#include "LED.h"

LED::LED(uint8_t pin, uint8_t default_value)
    : pin(pin), default_value(default_value) {}

void LED::setup() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, default_value);
}

void LED::update(uint8_t value) {
    digitalWrite(pin, value);
}
