# IRBazooka

![Alt text](/images/board_25.png)

This is the initial repository for our IoT Study Group.

The aim of this project is to create an automated way of turning off all the AC units in the office at some specified time, with the intention of reducing our energy consumption. Alexa integration is also on the roadmap, in order to control the AC units with only our voice power.

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

## Node-RED
### v0.1
- [ ] Use it directly with MQTT
### v1.0
- [ ] Create a node to interface with the firmware

# References
- Circuit inspired by [Harald Braun's IRBridge](https://www.hackster.io/har-bra/irbridge-controlling-ir-devices-via-alexa-web-interface-66ca06)
