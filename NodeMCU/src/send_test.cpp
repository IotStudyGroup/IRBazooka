#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED D2

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

uint16_t rawData1[74] = {0x01, 0x118c, 0x8a6, 0x153, 0x322, 0x153, 0x102, 0x151,
                         0x105, 0x151, 0x102, 0x151, 0x105, 0x151, 0x102, 0x151,
                         0x105, 0x151, 0x105, 0x151, 0x102, 0x151, 0x324, 0x153,
                         0x102, 0x151, 0x322, 0x153, 0x105, 0x151, 0x102, 0x15e,
                         0x0f8, 0x151, 0x102, 0x15e, 0x0f8, 0x151, 0x103, 0x151,
                         0x105, 0x151, 0x103, 0x150, 0x105, 0x150, 0x322, 0x153,
                         0x102, 0x151, 0x324, 0x151, 0x105, 0x151, 0x103, 0x151,
                         0x104, 0x151, 0x102, 0x151, 0x324, 0x151, 0x105, 0x151,
                         0x322, 0x154, 0x102, 0x15e, 0x0f8, 0x151, 0x322, 0x153,
                         0x102, 0x151};

uint16_t rawData2[68] = {0x001, 0x15e, 0x0f7, 0x151, 0x324, 0x151, 0x105, 0x151,
                         0x102, 0x15e, 0x0f8, 0x151, 0x102, 0x15e, 0x318, 0x15e,
                         0x317, 0x15e, 0x0f5, 0x153, 0x102, 0x15e, 0x0f5, 0x153,
                         0x102, 0x151, 0x104, 0x151, 0x322, 0x151, 0x104, 0x15e,
                         0x0f7, 0x151, 0x103, 0x15e, 0x0f7, 0x151, 0x102, 0x15e,
                         0x0f5, 0x151, 0x104, 0x15e, 0x0f8, 0x151, 0x102, 0x15e,
                         0x0f5, 0x151, 0x105, 0x15e, 0x0f5, 0x15e, 0x0f8, 0x151,
                         0x102, 0x151, 0x322, 0x153, 0x322, 0x160, 0x0f5, 0x15e,
                         0x0f6, 0x151};

void setup() {
  pinMode(IR_LED, OUTPUT);
  digitalWrite(IR_LED, HIGH);
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
}

void loop() {
  Serial.println("Sending OFF command...\n");
  irsend.sendRaw(rawData1, 74, 38);  // Send a raw data capture at 38kHz.
  // delay(100);
  irsend.sendRaw(rawData2, 68, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
}
