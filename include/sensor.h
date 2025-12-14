#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>

class Sensor {
public:
    Sensor(uint8_t pin, uint8_t type, size_t max_samples=60*24+1, unsigned long time_between_samples=60*1000);
    void setup();
    bool update(unsigned long delta_time);

    size_t get_samples() const;
    const float *get_temp_data() const;
    const float *get_humidity_data() const;

    ~Sensor();

private:
    DHT *dht;

    size_t samples;
    float *temp_data, *humidity_data;

    size_t max_samples;
    unsigned long time_between_samples;
    float time_since_last_sample;

    void sample();
};

#endif // SENSOR_H
