#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define RECV_PIN D1
#define BAUD_RATE 115200
#define CAPTURE_BUFFER_SIZE 1024
#define TIMEOUT 15U

IRrecv irrecv(RECV_PIN, CAPTURE_BUFFER_SIZE, TIMEOUT, true);

decode_results results;

void setup() {
    Serial.begin(BAUD_RATE, SERIAL_8N1, SERIAL_TX_ONLY);
    while (!Serial) {
        delay(50);
    }
    irrecv.enableIRIn();
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.printf("rawbuf: [");
        int i = 0;
        for (i=0; i<results.rawlen; i++) {
            Serial.printf("%x, ", results.rawbuf[i]);
        }
        Serial.printf("]\n");
    }
}
