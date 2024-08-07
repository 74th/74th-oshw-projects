/* Template app on which you can build your own. */

#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>

uint32_t loop_count_ms = 0;

#define CH217_EN_PIN GPIOv_from_PORT_PIN(GPIO_port_A, 2)
#define CH217_FLAG_PIN GPIOv_from_PORT_PIN(GPIO_port_C, 2)
#define SWITCH_PIN GPIOv_from_PORT_PIN(GPIO_port_C, 4)
#define LED_PIN GPIOv_from_PORT_PIN(GPIO_port_C, 1)

void setup()
{
	GPIO_port_enable(GPIO_port_A);
	GPIO_port_enable(GPIO_port_C);
	GPIO_port_enable(GPIO_port_D);

	GPIO_pinMode(CH217_EN_PIN, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CH217_FLAG_PIN, GPIO_pinMode_I_pullUp, GPIO_Speed_10MHz);
	GPIO_pinMode(SWITCH_PIN, GPIO_pinMode_I_pullUp, GPIO_Speed_10MHz);
	GPIO_pinMode(LED_PIN, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
}

#define STATE_OFF 0
#define STATE_ON 1
#define STATE_PUSHED_FROM_OFF 2
#define STATE_PUSHED_FROM_ON 3

#define HOLD_THREASHOLD_DURATION_MS 1000

uint8_t state = STATE_ON;

uint32_t push_start_ms = 0;
uint32_t flag_start_ms = 0;

void loop()
{
	uint8_t sw_pushed = !GPIO_digitalRead(SWITCH_PIN);
	uint8_t over_current = !GPIO_digitalRead(CH217_FLAG_PIN);
	uint8_t sw_led_on = 0;

	if (over_current)
	{
		if (flag_start_ms == UINT32_MAX)
		{
			flag_start_ms = loop_count_ms;
		}
		GPIO_digitalWrite_1(LED_PIN);
		if (((loop_count_ms - flag_start_ms) / 50) % 2)
		{
			GPIO_digitalWrite_1(LED_PIN);
		}
		else
		{
			GPIO_digitalWrite_0(LED_PIN);
		}
		if (!sw_pushed)
		{
			GPIO_digitalWrite_0(CH217_EN_PIN);
		}
		else
		{
			GPIO_digitalWrite_1(CH217_EN_PIN);
		}
	}
	else
	{
		flag_start_ms = UINT32_MAX;
	}

	if (sw_pushed)
	{
		if (loop_count_ms % 100 == 0)
			printf("p");
		switch (state)
		{
		case STATE_OFF:
			sw_led_on = 1;
			state = STATE_PUSHED_FROM_OFF;
			push_start_ms = loop_count_ms;
			break;
		case STATE_ON:
			sw_led_on = 1;
			state = STATE_PUSHED_FROM_ON;
			push_start_ms = loop_count_ms;
			break;
		case STATE_PUSHED_FROM_OFF:
			sw_led_on = 1;
			break;
		case STATE_PUSHED_FROM_ON:
			sw_led_on = 1;
			break;
		}
		GPIO_digitalWrite_1(CH217_EN_PIN);
	}
	else
	{
		uint32_t hold_duration_ms = loop_count_ms - push_start_ms;
		switch (state)
		{
		case STATE_OFF:
			GPIO_digitalWrite_1(CH217_EN_PIN);
			sw_led_on = 1;
			break;
		case STATE_ON:
			GPIO_digitalWrite_0(CH217_EN_PIN);
			sw_led_on = 0;
			break;
		case STATE_PUSHED_FROM_OFF:
			state = STATE_ON;
			GPIO_digitalWrite_0(CH217_EN_PIN);
			sw_led_on = 0;
			break;
		case STATE_PUSHED_FROM_ON:
			if (hold_duration_ms > HOLD_THREASHOLD_DURATION_MS)
			{
				state = STATE_OFF;
				GPIO_digitalWrite_1(CH217_EN_PIN);
				sw_led_on = 1;
			}
			else
			{
				state = STATE_ON;
				GPIO_digitalWrite_0(CH217_EN_PIN);
				sw_led_on = 0;
			}
			break;
		}
	}

	if (!over_current)
	{
		if (sw_led_on)
		{
			GPIO_digitalWrite_1(LED_PIN);
		}
		else
		{
			GPIO_digitalWrite_0(LED_PIN);
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
