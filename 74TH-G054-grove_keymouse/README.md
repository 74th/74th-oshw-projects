# Grove KeyMouse

USB キーボード、マウスエミュレータ CH9329 を搭載した Grove モジュール

PC のキーボードとマウスとして、UART で制御することができます。

CH9329 の使い方は、https://www.marutsu.co.jp/contents/shop/marutsu/datasheet/minnanolab_MR-CH9329EMU.pdf に詳しいです。また、拙著[『WCH の IC を活用する電子工作の本』](https://booth.pm/ja/items/5261331)でも少し解説しています。

## ピン配置

![ピン配置](./grove_keymouse.png)

CH9329 の電源は、USB 側から供給されます。

## v1.0.0

- 回路図: [PDF](./grove_keymouse-v1.0.0-semantics.pdf) [KiCanvas](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2F74th%2F74th-oshw-projects%2Fblob%2Fgrove-keymouse%2F1.0.0%2F74TH-G054-grove_keymouse%2Fgrove_keymouse.kicad_sch)
- PCB: [KiCanvas](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2F74th%2F74th-oshw-projects%2Fblob%2Fgrove-keymouse%2F1.0.0%2F74TH-G054-grove_keymouse%2Fgrove_keymouse.kicad_pcb)

### BOM

| Reference | Name                                        | Package         | Quantity |
| --------- | ------------------------------------------- | --------------- | -------- |
| C1-2      | Capacitor 100nF                             | SMD I0805 M2012 | 2        |
| C3        | Capacitor 1uF                               | SMD I0805 M2012 | 1        |
| CH1       | HY2.0 Socket SMD 4Pin (Grove) - UART Port.C |                 | 1        |
| D1        | LED Red                                     | SMD I0805 M2012 | 1        |
| D2        | LED Blue                                    | SMD I0805 M2012 | 1        |
| J1        | USB Type-A Plug                             |                 | 1        |
| R1        | Register 10kΩ                               | SMD I0805 M2012 | 1        |
| R2        | Register 5.1kRΩ                             | SMD I0805 M2012 | 1        |
| U1        | USB Keyboard Mouse Device IC CH9329         | SOIC-16         | 1        |
| U2        | USB Power Protection IC CH213K              | SOT-23          | 1        |
