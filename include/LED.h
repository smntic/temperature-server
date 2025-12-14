#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
    LED(uint8_t pin, uint8_t default_value);

    void setup();
    void update(uint8_t value);

private:
    uint8_t pin, default_value;
};

#endif // LED_H
