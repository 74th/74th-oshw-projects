#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_NeoPixel.h"

#define LED_PIN G27
#define BUTTON_PIN G39

Adafruit_NeoPixel pixels(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);

    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Wire.begin();
    pixels.begin();
}

bool btnStatePressed = false;

int programNum = 0;

void program0()
{
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
}
void program1()
{
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.show();
}
void program2()
{
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
    pixels.show();
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

    delay(10);
}