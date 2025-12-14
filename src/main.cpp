#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "LED.h"
#include "secrets.h"
#include "sensor.h"
#include "web_server.h"

Sensor *sensor;
LED *led;
WebServer *server;

void setup() {
    Serial.begin(9600); // can't leave this out for ESP8266

    sensor = new Sensor(D7, DHT22);
    led = new LED(D8, 0x0);
    server = new WebServer(WIFI_SSID, WIFI_PASSWORD);

    sensor->setup();
    led->setup();
    server->setup();
}

void loop(){
    const unsigned long delta_time = 20; // ms
    delay(delta_time);
    sensor->update(delta_time);
    led->update(server->status());
    server->update(sensor);
}
