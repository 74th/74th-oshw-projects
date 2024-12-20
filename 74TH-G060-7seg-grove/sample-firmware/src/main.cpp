#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_NeoPixel.h"

#define LED_PIN G27
#define BUTTON_PIN G39
#define I2C_SDA_PIN G26
#define I2C_SCL_PIN G32

#define SEG7_ADDR 0x73

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    pixels.begin();
}

bool btnStatePressed = false;

int programNum = 0;

int step = 0;

void program0()
{
    pixels.setPixelColor(0, pixels.Color(16, 0, 0));
    pixels.show();

    uint8_t c = 0;
    switch (step % 6)
    {
    case 0:
        c = 0x01;
        break;
    case 1:
        c = 0x02;
        break;
    case 2:
        c = 0x04;
        break;
    case 3:
        c = 0x08;
        break;
    case 4:
        c = 0x10;
        break;
    case 5:
        c = 0x20;
        break;
    }
    uint8_t msg[5] = {0x00, c, c, c, c};
    Wire.beginTransmission(SEG7_ADDR);
    Wire.write(msg, 5);
    Wire.endTransmission();
    printf("Sent 0-%d\n", step);

    step++;
}

void program1()
{
    pixels.setPixelColor(0, pixels.Color(0, 0, 16));
    pixels.show();

    uint8_t msg[5] = {0x00};
    if (step % 2 == 0)
    {
        msg[((step % 8) / 2) + 1] = 0x06;
    }
    else
    {
        msg[((step % 8) / 2) + 1] = 0x30;
    }

    Wire.beginTransmission(SEG7_ADDR);
    Wire.write(msg, 5);
    Wire.endTransmission();
    printf("Sent 1-%d\n", step);

    step++;
}

void program2()
{
    pixels.setPixelColor(0, pixels.Color(0, 16, 0));
    pixels.show();
    uint8_t msg[3] = {0x10, 0x00, 0x00};
    uint16_t num = step % 10000;
    msg[1] = num >> 8;
    msg[2] = num % 0x100;
    printf("Num: %x,%x\n", msg[1], msg[2]);

    Wire.beginTransmission(SEG7_ADDR);
    Wire.write(msg, 3);
    Wire.endTransmission();
    printf("Sent 1-%d\n", step);

    step++;
}
void loop()
{
    bool onTap = false;

    bool pushed = digitalRead(BUTTON_PIN);
    if (!pushed && btnStatePressed)
    {
        onTap = true;
    }
    btnStatePressed = pushed;

    if (onTap)
    {
        printf("Button pressed %d\n", programNum);
        programNum++;
        if (programNum > 2)
        {
            programNum = 0;
        }
    }

    switch (programNum)
    {
    case 0:
        program0();
        break;
    case 1:
        program1();
        break;
    case 2:
        program2();
        break;
    }

    delay(150);
}