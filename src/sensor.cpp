#include <Arduino.h>
#include <DHT.h>
#include "sensor.h"

Sensor::Sensor(uint8_t pin, uint8_t type, size_t max_samples, unsigned long time_between_samples) :
    dht(new DHT(pin, type)), samples(0), temp_data(new float[max_samples]),
    humidity_data(new float[max_samples]), max_samples(max_samples),
    time_between_samples(time_between_samples), time_since_last_sample(time_between_samples) {}

void Sensor::setup() {
    dht->begin();
}

bool Sensor::update(unsigned long delta_time) {
    time_since_last_sample += delta_time;
    if (time_since_last_sample >= time_between_samples) {
        sample();
        time_since_last_sample = time_since_last_sample-time_between_samples;
        return true;
    } else {
        return false;
    }
}

void Sensor::sample() {
    float t = dht->readTemperature();
    float h = dht->readHumidity();

    if (samples < max_samples) {
        temp_data[samples] = t;
        humidity_data[samples] = h;
        samples++;
    } else {
        for (size_t i = 1; i < samples; i++) {
            temp_data[i-1] = temp_data[i];
            humidity_data[i-1] = humidity_data[i];
        }
        temp_data[samples-1] = t;
        humidity_data[samples-1] = h;
    }
}

size_t Sensor::get_samples() const {
    return samples;
}

const float *Sensor::get_temp_data() const {
    return temp_data;
}

const float *Sensor::get_humidity_data() const {
    return humidity_data;
}

Sensor::~Sensor() {
    delete dht;
    delete[] temp_data;
    delete[] humidity_data;
}
