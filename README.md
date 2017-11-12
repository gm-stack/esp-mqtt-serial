# ESP-MQTT-Serial

## What?

Connects to a MQTT server, subscribes to a topic, and sends anything sent to that topic over a serial port (with optional header/trailer added).

## Why?

Control of projectors and other RS232 commandable devices from something like HomeAssistant.

## Tech Details

Written using the ESP8266 Arduino core, and uses PubSubClient for MQTT.

Copy `config.example.h` to `config.h` and edit.

## More info?

For more information, take a look at [my blog post on this project](https://stackunderflow.com/post/esp8266-mqtt-serial-projector-remote/)