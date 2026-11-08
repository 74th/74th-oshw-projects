/*
 * M5Stack ATOM Lite / Matrix と Grove KeyMouse を Port A で接続するサンプル。
 * ATOM のボタンを押すたびに、PC に「LGTM!」と Enter を入力する。
 * Grove KeyMouse は USB で入力先の PC に接続する。
 * Port A の GPIO32 を RX、GPIO26 を TX として、9600 bps で通信する。
 * シリアルモニター（115200 bps）に CH9329 の応答やエラーを表示する。
 */
#include <Arduino.h>

// M5Stack ATOM Lite / Matrix: Port A and the built-in button.
constexpr int kPortARxPin = 32;
constexpr int kPortATxPin = 26;
constexpr int kButtonPin = 39;
constexpr unsigned long kDebounceMs = 30;
constexpr unsigned long kResponseTimeoutMs = 500;
constexpr unsigned long kKeyIntervalMs = 50;
constexpr uint8_t kLeftShift = 0x02;

struct Response {
  uint8_t command;
  uint8_t length;
  uint8_t data[64];
};

struct KeyStroke {
  uint8_t modifier;
  uint8_t key;
};

const KeyStroke kMessage[] = {
    {kLeftShift, 0x0F},  // L
    {kLeftShift, 0x0A},  // G
    {kLeftShift, 0x17},  // T
    {kLeftShift, 0x10},  // M
    {kLeftShift, 0x1E},  // !
    {0x00, 0x28},        // Enter
};

void printByte(uint8_t value) {
  if (value < 0x10) Serial.print('0');
  Serial.print(value, HEX);
}

bool readResponse(uint8_t command, Response &response) {
  uint8_t packet[70];
  size_t count = 0;
  size_t expected = 5;
  const unsigned long start = millis();

  while (count < expected && millis() - start < kResponseTimeoutMs) {
    if (!Serial2.available()) {
      delay(1);
      continue;
    }
    packet[count++] = Serial2.read();
    if (count == 5) {
      if (packet[4] > sizeof(response.data)) {
        Serial.println("ERROR: response length exceeds 64 bytes");
        return false;
      }
      expected = 6 + packet[4];
    }
  }

  Serial.print("CH9329 RX:");
  for (size_t i = 0; i < count; ++i) {
    Serial.print(' ');
    printByte(packet[i]);
  }
  Serial.println();
  if (count != expected) {
    Serial.println("ERROR: CH9329 response timeout");
    return false;
  }
  uint8_t checksum = 0;
  for (size_t i = 0; i < count - 1; ++i) checksum += packet[i];
  if (packet[0] != 0x57 || packet[1] != 0xAB || packet[2] != 0x00 ||
      checksum != packet[count - 1]) {
    Serial.println("ERROR: invalid CH9329 response");
    return false;
  }
  response.command = packet[3];
  response.length = packet[4];
  for (size_t i = 0; i < response.length; ++i) {
    response.data[i] = packet[5 + i];
  }
  if (response.command != (command | 0x80)) {
    Serial.println("ERROR: CH9329 returned an error or unexpected command");
    return false;
  }
  return true;
}

bool sendCommand(uint8_t command, const uint8_t *data, size_t length,
                 Response &response) {
  if (Serial2.available()) {
    Serial.print("Unexpected pending RX:");
    while (Serial2.available()) {
      Serial.print(' ');
      printByte(Serial2.read());
    }
    Serial.println();
  }
  uint8_t packet[70] = {0x57, 0xAB, 0x00, command, static_cast<uint8_t>(length)};
  for (size_t i = 0; i < length; ++i) packet[5 + i] = data[i];
  uint8_t checksum = 0;
  for (size_t i = 0; i < 5 + length; ++i) checksum += packet[i];
  packet[5 + length] = checksum;
  Serial2.write(packet, 6 + length);
  Serial2.flush();
  return readResponse(command, response);
}

bool sendKeyboardReport(uint8_t modifier, uint8_t key) {
  const uint8_t data[] = {modifier, 0x00, key, 0x00, 0x00, 0x00, 0x00, 0x00};
  Response response;
  if (!sendCommand(0x02, data, sizeof(data), response)) return false;
  if (response.length != 1 || response.data[0] != 0x00) {
    Serial.println("ERROR: keyboard command failed");
    return false;
  }
  return true;
}

void typeMessage() {
  Response response;
  if (!sendCommand(0x01, nullptr, 0, response)) return;
  if (response.length != 8) {
    Serial.println("ERROR: unexpected GET_INFO response length");
    return;
  }
  if (response.data[1] != 0x01) {
    Serial.println("ERROR: Grove KeyMouse USB is not recognized by the PC");
    return;
  }
  Serial.println("USB recognized; sending LGTM! and Enter");
  if (response.data[2] & 0x02) Serial.println("NOTE: Caps Lock is on");
  for (const KeyStroke &stroke : kMessage) {
    const bool pressed = sendKeyboardReport(stroke.modifier, stroke.key);
    delay(kKeyIntervalMs);
    const bool released = sendKeyboardReport(0x00, 0x00);
    if (!pressed || !released) {
      Serial.println("ERROR: typing stopped; check for a stuck key");
      return;
    }
    delay(kKeyIntervalMs);
  }
  Serial.println("Done");
}

void setup() {
  Serial.begin(115200);
  pinMode(kButtonPin, INPUT);
  Serial2.begin(9600, SERIAL_8N1, kPortARxPin, kPortATxPin);
  Serial.println("Press the ATOM button to type LGTM! and Enter");
}

void loop() {
  static bool lastReading = HIGH;
  static bool buttonState = HIGH;
  static unsigned long lastChange = 0;

  const bool reading = digitalRead(kButtonPin);
  if (reading != lastReading) {
    lastChange = millis();
    lastReading = reading;
  }
  if (reading != buttonState && millis() - lastChange >= kDebounceMs) {
    buttonState = reading;
    if (buttonState == LOW) {
      typeMessage();
    }
  }
}
