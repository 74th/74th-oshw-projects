/* Template app on which you can build your own. */

#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>

uint32_t loop_count_ms = 0;

#define CH217_EN_PIN GPIOv_from_PORT_PIN(GPIO_port_A, 2)
#define CH217_FLAG_PIN GPIOv_from_PORT_PIN(GPIO_port_C, 2)
#define SWITCH_FLAG_PIN GPIOv_from_PORT_PIN(GPIO_port_D, 4)

void setup()
{
	GPIO_port_enable(GPIO_port_A);
	GPIO_port_enable(GPIO_port_C);
	GPIO_port_enable(GPIO_port_D);

	GPIO_pinMode(CH217_EN_PIN, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CH217_FLAG_PIN, GPIO_pinMode_I_pullUp, GPIO_Speed_10MHz);
	GPIO_pinMode(SWITCH_FLAG_PIN, GPIO_pinMode_I_pullUp, GPIO_Speed_10MHz);
}

#define STATE_OFF 0
#define STATE_ON 1
#define STATE_PUSHED_FROM_OFF 2
#define STATE_PUSHED_FROM_ON 3

#define HOLD_THREASHOLD_DURATION_MS 1000

uint8_t state = STATE_ON;

uint32_t push_start_ms = 0;

void loop()
{
	uint8_t sw = GPIO_digitalRead(SWITCH_FLAG_PIN);
	if (sw)
	{
		uint32_t hold_duration_ms = loop_count_ms - push_start_ms;
		// unpushed
		switch (state)
		{
		case STATE_OFF:
			GPIO_digitalWrite_1(CH217_EN_PIN);
			break;
		case STATE_ON:
			GPIO_digitalWrite_0(CH217_EN_PIN);
			break;
		case STATE_PUSHED_FROM_OFF:
			state = STATE_ON;
			GPIO_digitalWrite_0(CH217_EN_PIN);
			break;
		case STATE_PUSHED_FROM_ON:
			if (hold_duration_ms > HOLD_THREASHOLD_DURATION_MS)
			{
				state = STATE_OFF;
				GPIO_digitalWrite_1(CH217_EN_PIN);
			}
			else
			{
				state = STATE_ON;
				GPIO_digitalWrite_0(CH217_EN_PIN);
			}
			break;
		}
	}
	else
	{
		// pushed
		switch (state)
		{
		case STATE_OFF:
			GPIO_digitalWrite_0(CH217_EN_PIN);
			state = STATE_PUSHED_FROM_OFF;
			push_start_ms = loop_count_ms;
			break;
		case STATE_ON:
			GPIO_digitalWrite_1(CH217_EN_PIN);
			state = STATE_PUSHED_FROM_ON;
			push_start_ms = loop_count_ms;
			break;
		case STATE_PUSHED_FROM_OFF:
			GPIO_digitalWrite_0(CH217_EN_PIN);
			break;
		case STATE_PUSHED_FROM_ON:
			GPIO_digitalWrite_1(CH217_EN_PIN);
			break;
		}
	}
}

int main()
{
	SystemInit();

	setup();

	while (1)
	{
		loop();
		Delay_Ms(1);
		loop_count_ms++;
	}
}
