#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <IRsend.h>
#include <string.h>

#define SSID ""
#define PASS ""

#define MQTT_SERVER ""
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASS ""

#define OTA_PASS "UPDATE_PW"
#define OTA_PORT 8266

// #define LED_PIN D0

#define IR_PIN D2

#define ESP_NAME "IRBAZOOKA"

const char* irTopic = "ckl/funroom/projector";

WiFiClient espClient;
PubSubClient client(espClient);

IRsend irsend(IR_PIN);
const uint64_t PROJECTOR_POWER = 0xC1AA09F6;

uint64_t lastMQTTCheck = -10000;

void initWifi() {
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASS);
}

void checkMQTTConnection() {
    Serial.print("Checking MQTT connection: ");
    if (client.connected()) {
        Serial.println("OK");
    } else {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.print("new connection: ");
            if (client.connect(ESP_NAME, MQTT_USER, MQTT_PASS)) {
                Serial.println("connected");
                client.subscribe(irTopic);
            } else {
                Serial.print("failed, rc=");
                Serial.println(client.state());
            }
        } else {
            Serial.println(" Not connected to WiFI AP, abandoned connect.");
        }
    }
    if (client.connected()) {
        // digitalWrite(LED_PIN, HIGH);
    } else {
        // digitalWrite(LED_PIN, LOW);
    }
}

void MQTTcallback(char* payloadTopic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(irTopic);
    Serial.println("] ");

    if (strcmp(payloadTopic, irTopic) == 0) {
      Serial.println("SENDING COMMAND");
        irsend.sendNEC(PROJECTOR_POWER, 32);
    }
}

void setup() {
    pinMode(IR_PIN, OUTPUT);
    digitalWrite(IR_PIN, LOW);
    irsend.begin();
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

    initWifi();

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(MQTTcallback);

    ArduinoOTA.setPort(OTA_PORT);
    ArduinoOTA.setHostname(ESP_NAME);
    ArduinoOTA.setPassword(OTA_PASS);
    ArduinoOTA.begin();
}

void loop() {
    if (millis() - lastMQTTCheck >= 10000) {
        checkMQTTConnection();
        lastMQTTCheck = millis();
    }

    // Handle any pending MQTT messages
    client.loop();

    // Handle any pending OTA SW updates
    ArduinoOTA.handle();
}
