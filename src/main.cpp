#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "secrets.h"
#include "website.h"

const int STATUS_LED_PIN = D8;

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const long timeoutTime = 2000;

WiFiServer server(80);

void setup() {
    Serial.begin(9600);

    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

String prepareHtmlPage() {
    float *tempData = new float[5]{1, 2, 3, 4, 5};
    float *humidityData = new float[5]{50, 60, 70, 80, 90};
    return generate_website(tempData, humidityData, 5);
}

void loop(){
    delay(20);
    digitalWrite(STATUS_LED_PIN, WiFi.status() == WL_CONNECTED ? HIGH : LOW);

    WiFiClient client = server.accept();
    if (client) {
        Serial.println("\nClient connected");
        while (client.connected()) {
            // read line by line what the client (web browser) is requesting
            if (client.available()) {
                String line = client.readStringUntil('\r');
                Serial.print(line);
                // wait for end of client's request, that is marked with an empty line
                if (line.length() == 1 && line[0] == '\n') {
                    client.println(prepareHtmlPage());
                    break;
                }
            }
        }

        while (client.available()) {
            client.read();
        }

        // close the connection:
        client.stop();
        Serial.println("Client disconnected");
    }
}

/* temperature + humidity sensor part
#include "DHT.h"

const int DHTPIN = D7;
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

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
*/
