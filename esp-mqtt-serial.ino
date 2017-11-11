// ESP8266 remote projector control
// gm@stackunderflow.com
// largely based on PubSubClient example...

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

#include "config.h"

// internal vars
WiFiClient espClient;
PubSubClient client(espClient);
long lastReconnect;


void setup() {
  Serial.begin(115200);
  Serial1.begin(serial_baud);

  Serial.printf("\nConnecting to %s", wifi_ssid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(net_hostname);
  WiFi.begin(wifi_ssid, wifi_pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("\nConnected, IP is:");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_host, mqtt_port);
  client.setCallback(mqtt_received);

  lastReconnect = 0;
}

void loop() {
  if (!client.connected()) {
    long startConnect = millis();
    if ((startConnect - lastReconnect) > 1000) {
      lastReconnect = startConnect;
      if (client.connect(net_hostname, mqtt_user, mqtt_pass)) {
        Serial.println("MQTT connected");
        if (client.subscribe(mqtt_topic)) {
          Serial.printf("Subscribed to topic %s\n", mqtt_topic);
        } else {
          Serial.printf("Failed to subscribe to topic %s\n", mqtt_topic);
        }
      } else {
        Serial.println("MQTT connect failed, retrying");
      }
      if (client.connected()) {
        lastReconnect = 0;
      }
    }
  }

  client.loop();
}

void mqtt_received(char* topic, byte* data, unsigned int data_len) {

  Serial.print("Message received [");
  Serial.print(topic);
  Serial.print("] ");

  Serial1.print(serial_head);

  for (int i = 0; i < data_len; i++) {
    Serial.print((char)data[i]);
    Serial1.print((char)data[i]);
  }
  Serial.println();

  Serial1.print(serial_tail);

}