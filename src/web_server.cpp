#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "web_server.h"
#include "website.h"

WebServer::WebServer(const char *ssid, const char *password, int port, long timeout_time)
    : server(new WiFiServer(port)), ssid(strdup(ssid)), password(strdup(password)), port(port),
      timeout_time(timeout_time) {}

void WebServer::setup() {
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
    server->begin();
}

void WebServer::update(const Sensor *sensor) {
    accept_clients(sensor);
}

void WebServer::accept_clients(const Sensor *sensor) {
    WiFiClient client = server->accept();
    if (client) {
        Serial.println("\nClient connected");
        while (client.connected()) {
            // Read line by line what the client is requesting
            if (client.available()) {
                String line = client.readStringUntil('\r');
                Serial.print(line);
                // Wait for end of client's request. Marked with an empty line
                if (line.length() == 1 && line[0] == '\n') {
                    client.print(WEBSITE_1);
                    for (size_t i = 0; i < sensor->get_samples(); i++) {
                        client.print(sensor->get_temp_data()[i]);
                        if (i < sensor->get_samples()-1) client.print(",");
                    }
                    client.print(WEBSITE_2);
                    for (size_t i = 0; i < sensor->get_samples(); i++) {
                        client.print(sensor->get_humidity_data()[i]);
                        if (i < sensor->get_samples()-1) client.print(",");
                    }
                    client.print(WEBSITE_3);
                    client.println();
                    break;
                }
            }
        }

        while (client.available()) {
            client.read();
        }

        // Close the connection
        client.stop();
        Serial.println("Client disconnected");
    }
}

bool WebServer::status() const {
    return WiFi.status() == WL_CONNECTED;
}

WebServer::~WebServer() {
    delete server;

    delete[] ssid;
    delete[] password;
}
