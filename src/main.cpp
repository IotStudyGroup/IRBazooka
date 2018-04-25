#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <ArduinoJson.h>
#include <IRutils.h>
#include <vector>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define RECV_PIN D3
#define IR_LED D2
#define BAUD_RATE 115200
#define CAPTURE_BUFFER_SIZE 1024
#define TIMEOUT 50U

#define SSID "CKL-DEV"
#define WIFI_PASSWORD "xcake1002"

#define MQTT_SERVER "192.168.0.145"
#define MQTT_PORT 1883

#define ESP_NAME "IRBazooka"

#define LEARN_TOPIC ESP_NAME "/learn"
#define EXECUTE_TOPIC ESP_NAME "/execute"

#define LEARNT_COMMAND_TOPIC ESP_NAME "/learnt"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

IRrecv irrecv(RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);
IRsend irsend(IR_LED);

decode_results results;

String toJsonString(volatile uint16_t* buffer, size_t size) {
    DynamicJsonBuffer jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    JsonArray& data = root.createNestedArray("data");

    for (uint16_t i = 1; i < size; ++i) {
        String output = "";
        uint32_t usecs;
        for (usecs = buffer[i] * RAWTICK; usecs > UINT16_MAX; usecs -= UINT16_MAX) {
            output += uint64ToString(UINT16_MAX);
            if (i % 2)
            output += ", 0,  ";
            else
            output += ",  0, ";
        }
        output += uint64ToString(usecs, 10);

        data.add(output.toInt());
    }

    String resultString;
    root.printTo(resultString);
    return resultString;
}

String recordIRSignal() {
    digitalWrite(BUILTIN_LED, LOW);
    irrecv.enableIRIn();

    String resultString;
    while (true) {
        if (irrecv.decode(&results)) {
            resultString = toJsonString(results.rawbuf, results.rawlen);
            break;
        }
        delay(500);
    }

    irrecv.disableIRIn();
    digitalWrite(BUILTIN_LED, HIGH);
    return resultString;
}

void fromJsonString(String jsonString, uint16_t* result, size_t* size) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonString);

    JsonArray& irPacket = root["data"];

    for (int i = 0; i < irPacket.size(); ++i) {
        result[i] = irPacket[i];
    }
    *size = irPacket.size();
}

void executeIRSignal(String irSignal) {
    size_t size = 0;
    uint16_t result[1024];
    fromJsonString(irSignal, result, &size);
    irsend.sendRaw(result, size, 38);

    digitalWrite(BUILTIN_LED, LOW);
    delay(1000);
    digitalWrite(BUILTIN_LED, HIGH);

}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    if (strcmp(topic, LEARN_TOPIC) == 0) {
        String command = recordIRSignal();

        client.publish(LEARNT_COMMAND_TOPIC, command.c_str());
    } else if (strcmp(topic, EXECUTE_TOPIC)) {
        Serial.println("Executing Signal");
        char irSignal[length];
        for (int i = 0; i < length; ++i) {
            irSignal[i] = (char) payload[i];
        }
        executeIRSignal(String(irSignal));
    }
}

void setupWiFi() {
    WiFi.begin(SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    digitalWrite(BUILTIN_LED, LOW);
    pinMode(IR_LED, OUTPUT);
    digitalWrite(IR_LED, LOW);

    Serial.begin(BAUD_RATE, SERIAL_8N1, SERIAL_TX_ONLY);
    while (!Serial) {
        delay(50);
    }

    setupWiFi();

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(mqttCallback);

    irsend.begin();
}

void connectToBroker() {
    while (!client.connected()) {
        Serial.println("Connecting to the broker");
        if (client.connect(ESP_NAME)) {
            Serial.println("Connected");
            client.subscribe(LEARN_TOPIC);
            client.subscribe(EXECUTE_TOPIC);

            digitalWrite(BUILTIN_LED, HIGH);
        } else {
            Serial.println("Failed to connect, trying again in 5 seconds");
            delay(5000);
        }
    }
}

void loop() {

    if (!client.connected()) {
        connectToBroker();
    }

    client.loop();

    return;
    if (irrecv.decode(&results)) {
        String resultString = toJsonString(results.rawbuf, results.rawlen);
        Serial.println("got string");
        Serial.println(resultString);

        size_t size = 0;
        uint16_t result[1024];
        fromJsonString(resultString, result, &size);

        delay(5000);

        Serial.println("Got");
        Serial.println(result[0]);
        irsend.sendRaw(result, size, 38);
    }
}
