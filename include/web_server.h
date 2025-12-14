#ifndef SERVER_H
#define SERVER_H

#include <ESP8266WiFi.h>
#include "sensor.h"

class WebServer {
public:
    WebServer(const char *ssid, const char *password, int port=80, long timeout_time=2000);
    void setup();
    void update(const Sensor *sensor);
    bool status() const;

    ~WebServer();

private:
    WiFiServer *server;

    const char *ssid, *password;
    int port;
    long timeout_time;

    void accept_clients(const Sensor *sensor);
};

#endif // SERVER_H
