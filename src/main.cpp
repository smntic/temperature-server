#include "Arduino.h"
#include "DHT.h"

const int DHTPIN = D7;
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const int STATUS_LED_PIN = D8;

void setup() {
    pinMode(STATUS_LED_PIN, OUTPUT);
    Serial.begin(9600);

    dht.begin();
}

void loop() {
    delay(1000);

    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(100);
    digitalWrite(STATUS_LED_PIN, LOW);

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%  Temperature: ");
    Serial.print(t);
    Serial.print("°C ");
    Serial.println();
}
