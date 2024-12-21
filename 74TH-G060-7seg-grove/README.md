# 7Seg Grove

This module allows you to control four 7-segment LEDs using I2C signals through a Grove connector.

> [!Caution]
> WIP

![alt text](3d_render-2.png)

![alt text](3d_render-1.png)

- Semantics: [kicanvas](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2F74th%2F74th-oshw-projects%2Fblob%2Fmain%2F74TH-G060-7seg-grove%2F74TH-G060-7seg-grove.kicad_sch)
- PCB: [kicanvas](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2F74th%2F74th-oshw-projects%2Fblob%2Fmain%2F74TH-G060-7seg-grove%2F74TH-G060-7seg-grove.kicad_pcb)
- Firmware: [./firmware (using ch32v003fun)](./firmware)

## I2C Protocol

- Address: 0x73

### Registers

| address |                                               | R/W | reset |
| ------- | --------------------------------------------- | --- | ----- |
| 0x00    | Direct IO for LED 1                           | R/W | 0x00  |
| 0x01    | Direct IO for LED 2                           | R/W | 0x00  |
| 0x02    | Direct IO for LED 3                           | R/W | 0x00  |
| 0x03    | Direct IO for LED 4                           | R/W | 0x00  |
| 0x10    | Number uint16 input(Upper bit)                | W   | 0x00  |
| 0x11    | Number uint16 input(lower bit)                | W   | 0x00  |
| 0x12    | Point location(0x00 is OFF) (Not Impremented) | W   | 0x00  |

#### Direct IO bits

- bit 1: LED A(1: ON, 0: OFF)
- bit 2: LED B(1: ON, 0: OFF)
- bit 3: LED C(1: ON, 0: OFF)
- bit 4: LED D(1: ON, 0: OFF)
- bit 5: LED E(1: ON, 0: OFF)
- bit 6: LED F(1: ON, 0: OFF)
- bit 7: LED G(1: ON, 0: OFF)
- bit 8: LED DP(1: ON, 0: OFF)

<img src="7seg_map.drawio.svg" width="200px"/>

## BOM

### 1.0.0-1.0.1

| Reference | Name                                                 | Package         | Quantity |
| --------- | ---------------------------------------------------- | --------------- | -------- |
| C1        | Capacitor 100nF                                      | SMD I0603 M1608 | 1        |
| C2-3      | Capacitor 10uF                                       | SMD I0603 M1608 | 2        |
| CH2       | HY2.0 (Grove) or SH1.0 (Qwiic) Socket SMD 4Pin - I2C |                 | 1        |
| D1        | LED LED                                              | SMD I0805 M2012 | 1        |
| JP1       | Jumper INPUT 3V3                                     |                 | 1        |
| R1-8      | Register 100Ω                                        | SMD I0603 M1608 | 8        |
| R9        | Register 10kΩ                                        | SMD I0603 M1608 | 1        |
| R10-11    | Register 1kΩ                                         | SMD I0603 M1608 | 2        |
| U1-4      | 7Seg LED                                             | TH              | 4        |
| U5        | MCU WCH CH32V003F4P6                                 | TSSOP20         | 1        |
| U6        | USB Power Protection IC CH213K                       | SOT-23          | 1        |
| U7        | Regulator 3.3V AMS1117-3.3                           | SOT-89          | 1        |