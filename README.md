ESP32-MQTT-Thingsboard

ESP microcontroller and sensors project for measuring temperature, humidity, pressure, and differential pressure. The project includes connecting the ESP to the internet via an Ethernet connection, sending data to an MQTT server, and displaying the data on a user dashboard using ThingsBoard.io. In repository is also a client that reads from MQTT server.

## Features

- Measure temperature, humidity, pressure, and differential pressure using various sensors.
- Connect the ESP microcontroller to the internet via Ethernet.
- Send random data from the ESP to an MQTT server.
- Establish communication with sensors and retrieve data on the ESP.
- Send sensor data from the ESP to an MQTT server.
- Create a Python client to retrieve data from the MQTT server and display it on a ThingsBoard.io dashboard.

## Components

- ESP32 OLIMEX PoE ISO
- Temperature Sensor
- Humidity Sensor
- Pressure Sensor
- Differential Pressure Sensor
- Ethernet Module
- USB Cable
- Ethernet Cable

## Prerequisites

- Arduino IDE installed
- Required libraries installed (ETH.h, TE_SM9000.h, SparkFun_PHT_MS8607_Arduino_Library.h, PubSubClient.h, Wire.h>)
- MQTT server setup
- ThingsBoard.io account for the dashboard
- Replace the placeholders in the code with your network and MQTT server credentials
