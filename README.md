# IRBazooka

![Alt text](/images/board_25.png)

This is the initial repository for our IoT Study Group.

The aim of this project is to create an automated way of turning off all the AC units in the office at some specified time, with the intention of reducing our energy consumption. Alexa integration is also on the roadmap, in order to control the AC units with only our voice power.

# Instructions

```bash
$ git clone --recursive https://github.com/IotStudyGroup/IRBazooka.git
```

## Folder structure

- Eagle
  - PCB files.
- Led-holder
  - 3D Printed files for the LED holder. You don't actually need it. But it makes it easier to position the LEDs.
- NodeMCU
  - Firmware (WORKING IN PROGRESS - NOT USABLE YET)
- OpenMQTTGateway (git submodule)
  - open firmware that works great!

# Bill Of Materials
These are the components necessary to build the board
```
Qty   Value            Description

 2    10kΩ             10kΩ resistor
 3    1kΩ              1kΩ resistor
 7    2N3904           NPN Transistror
 1    S8550            PNP Transistror
 1    ESP12E_DEVKIT    NodeMCU v2
 6    LED-IRTSAL6100   Infrared LED (IR)
 1    TSOP4838         IR Receiver and Demodulator
 ```
 Link for buying at Filipe Flop:<br>
 * [10kΩ resistor](https://www.filipeflop.com/produto/resistor-10k%CF%89-14w-x20-unidades/)<br>
 * [1kΩ resistor](https://www.filipeflop.com/produto/resistor-1k%CF%89-14w-x20-unidades/)<br>
 * [2N3904](https://www.filipeflop.com/produto/transistor-2n3904-npn-x10-unidades/)<br>
 * [S8550](https://www.filipeflop.com/produto/transistor-s8550-pnp-x10-unidades/)<br>
 * [ESP12E_DEVKIT](https://www.filipeflop.com/produto/modulo-wifi-esp8266-nodemcu-esp-12/)<br>
 * [LED-IRTSAL6100](https://www.filipeflop.com/produto/led-emissor-infravermelho-ir-5mm/)<br>
 * [TSOP4838](https://www.filipeflop.com/produto/receptor-infravermelho-ir-tsop4838/)<br>

# Roadmap
## Firmware
For now we are using a modified version of the [OpenMQTTGateway](https://github.com/marciogranzotto/OpenMQTTGateway). You can check the documenation of that project to find out how to use it.
However, in the future, we intend to create our own firmware. That code is inside the `NodeMCU` folder.

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
