# IRBazooka

![Alt text](/images/board_25.png)

This is the initial repository for our IoT Study Group.

The aim of this project is to create an automated way of turning off all the AC units in the office at some specified time, with the intention of reducing our energy consumption. Alexa integration is also on the roadmap, in order to control the AC units with only our voice power.

# Bill Of Materials
These are the components necessary to build the board
```
Qty   Value            Description

 2    10kΩ             10kΩ resistor
 3    1k               1kΩ resistor
 7    2N3904           NPN TRANSISTORe
 1    S8550            PNP Transistror
 1    ESP12E_DEVKIT    NodeMCU v2
 6    LED-IRTSAL6100   Infrared LED (IR)
 1    TSOP4838         IR Receiver and Demodulator
 ```

# Roadmap
## Firmware
### v0.1
- [x] Read IR signals
- [x] Send IR signals

### v1.0
- [ ] Connect to an WiFi network and handle reconnection
- [ ] Connect to an MQTT broker and handle reconnection
- [ ] Read IR signals and publish the data on an MQTT topic
- [ ] Subscribe to MQTT topic and send data to IR

### v2.0
- [ ] Web interface to configure MQTT broker address and topics
- [ ] OTA firmware update

# References
- Circuit inspired by [Harald Braun's IRBridge](https://www.hackster.io/har-bra/irbridge-controlling-ir-devices-via-alexa-web-interface-66ca06)
