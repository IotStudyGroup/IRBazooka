#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRsend.h>
#include <ArduinoJson.h>
#include <IRutils.h>
#include <vector>

#define RECV_PIN D3
#define IR_LED D2
#define BAUD_RATE 115200
#define CAPTURE_BUFFER_SIZE 1024
#define TIMEOUT 50U

IRrecv irrecv(RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);
IRsend irsend(IR_LED);

decode_results results;

void setup() {

    pinMode(IR_LED, OUTPUT);
    digitalWrite(IR_LED, LOW);

    Serial.begin(BAUD_RATE, SERIAL_8N1, SERIAL_TX_ONLY);
    while (!Serial) {
        delay(50);
    }
    irrecv.enableIRIn();
    irsend.begin();
}

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

void fromJsonString(String jsonString, uint16_t* result, size_t* size) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(jsonString);

    JsonArray& irPacket = root["data"];

    for (int i = 0; i < irPacket.size(); ++i) {
        result[i] = irPacket[i];
    }
    *size = irPacket.size();
}

void loop() {
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
