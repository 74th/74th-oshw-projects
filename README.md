# @74th's public PCB projects

@74th の公開している PCB のプロジェクト

> [!Caution]
> 2024/08/08 Directory structure changed (added IDs for 74TH-G050, etc.). Some of the links printed in the instruction manuals of the PCBs we used to distribute may be broken. Please read and use them as appropriate.
> ※ 2024/08/08 ディレクトリ構成を変更しました（74TH-G050 等の ID を追加しました）。一部、かつてに頒布した基板の取説で印刷したリンクが切れている場合があります。 適宜、読み替えて利用をお願いします。


## Projects included in this repository

このリポジトリに含まれているプロジェクト

### Main project

- 2024-12 [[74TH-G060]7Seg Grove](./74TH-G060-7seg-grove/): four 7-segment LEDs using the I2C protocol via Grove: Groveで
- 2024-08 [[74TH-G054]Grove Keymouse](./74TH-G054-grove_keymouse/): Grove UART device that uses CH9329 to act as keyboard and mouse via UART. CH9329 を使って UART 経由でキーボード、マウスとして振るわせる、Grove UART デバイス
- 2024-07 [[74TH-G053]USB Switch Adapter](./74TH-G053-usb_switch_adapter/): スイッチを追加する USB アダプタ
- 2024-06 [[74TH-G050]Grove Universal Board](./74TH-G050-grove_universal_board/): Grove デバイスを作るための小型ユニバーサル基板
- 2024-06 [[74TH-G049]Grove Qwiic debug adapter](./74TH-G049-grove_qwiic_debug_adapter/): Grove と qwiic の信号を読み取るアダプタ
- 2024-05 [[74TH-G048]Grove Qwiic breadboard bridge](./74TH-G048-grove_qwiic_breadboard_bridge/): ブレッドボードで Grove、Qwiic を扱う為のアダプタ。I2C プルアップ付き。

### Sub project

- 2024-07 [MISC-usb_adapter_a-male_to_c-female](./MISC-usb_adapter_a-male_to_c-female/): USB Type-A オス → USB Type-C メス アダプタ

### Testing

- 2024-05 [TEST-test-lipo_battery](./TEST-test-lipo_battery/): リポバッテリー充電 IC と、DCDC コンバータの、74th の学習用基盤

##  Other @74th OSH projects (with publicly available KiCad files)

その他の @74th の OSH プロジェクト（KiCad ファイルを公開しているもの）

- [74th/ch32v-dev-boards](https://github.com/74th/ch32v-dev-boards): Development boards using WCH's RISC-V MCU, CH32V series. WCH の RISC-V MCU、CH32V シリーズを使った開発ボード
- [74th/esp32-dev-boards](https://github.com/74th/esp32-dev-boards): Development boards using Espressif's ESP32 series. Espressif の ESP32 シリーズを使った開発ボード
- [74th/stm32-promicro](https://github.com/74th/stm32-promicro): ProMicro type development board using STMicro's STM32 series. STMicro の STM32 シリーズを使った ProMicro 型開発ボード
- [74th/esp32c3-iot-client-board](https://github.com/74th/esp32c3-iot-client-board): IoT client board using Espressif's ESP32-C3. Espressif の ESP32-C3 を使った IoT クライアントボード
- [74th/tv-side-keyboard-SparrowTV](https://github.com/74th/tv-side-keyboard-SparrowTV):  TV side keyboard. TV 横キーボード
- [74th/relay-switch-usbhub](https://github.com/74th/relay-switch-usbhub): USB hub that switches using relays. リレーを使ってスイッチする USB ハブ
- [74th/ch32v203-daplink-pcb](https://github.com/74th/ch32v203-daplink-pcb): CH32V203 を使った DAPLink
- [74th/usb-c-dip-kit](https://github.com/74th/usb-c-dip-kit):  DIP a Type-C socket. Type-C ソケットを DIP 化

## Using KiCad ライブラリ

- [74th/kicad-parts](https://github.com/74th/74th-kicad-parts): KiCad library used by 74th. 74th が利用している KiCad ライブラリ

## License

MIT License
