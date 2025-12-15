# ESP8266 Temperature Web Server

![web server example](./docs/example.png)

## Features

- View current temperature and humidity and see trends in recent data with graphs
- Select from multiple time ranges ranging from 24 hours to 15 minutes

## Circuit Design

![circuit schematic](./docs/schematic.png)

## Setup

Upload the program onto an ESP8266-12E-style board via platformio:

```bash
pio run --target upload`
```

The program will output the server address to a serial monitor.
You can also find it on your router's homepage.
