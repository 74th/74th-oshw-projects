#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>
#include <stdbool.h>

#define CTL1 GPIOv_from_PORT_PIN(GPIO_port_D, 4)
#define CTL2 GPIOv_from_PORT_PIN(GPIO_port_D, 5)
#define CTL3 GPIOv_from_PORT_PIN(GPIO_port_D, 6)
#define CTL4 GPIOv_from_PORT_PIN(GPIO_port_A, 1)
#define CTL5 GPIOv_from_PORT_PIN(GPIO_port_A, 2)
#define CTL6 GPIOv_from_PORT_PIN(GPIO_port_D, 0)
#define CTL7 GPIOv_from_PORT_PIN(GPIO_port_C, 6)
#define CTL8 GPIOv_from_PORT_PIN(GPIO_port_C, 7)
#define CTL9 GPIOv_from_PORT_PIN(GPIO_port_D, 2)
#define CTL10 GPIOv_from_PORT_PIN(GPIO_port_D, 3)
#define PINS 10

#define ENABLE_DEBUGGING 0

bool enable_led = false;

void setup()
{
	GPIO_port_enable(GPIO_port_A);
	GPIO_port_enable(GPIO_port_C);
	GPIO_port_enable(GPIO_port_D);

	GPIO_pinMode(CTL1, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL2, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL3, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL4, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL5, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL6, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL7, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL8, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL9, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);
	GPIO_pinMode(CTL10, GPIO_pinMode_O_pushPull, GPIO_Speed_10MHz);

	Delay_Ms(1);
}

uint32_t current_tick_us()
{
	return SysTick->CNT / DELAY_US_TIME;
}

#define STEP_US 300000

void main_loop()
{
	uint32_t start_us = current_tick_us();

	while (1)
	{
		uint32_t now_us = current_tick_us();

		if (now_us < start_us)
		{
			start_us = 0;
			continue;
		}

		uint32_t elappsed_us = now_us - start_us;
		uint32_t target_pin = elappsed_us / STEP_US;
#if ENABLE_DEBUGGING
		printf("target_pin: %d\n", target_pin);
#endif

		if (target_pin == 0)
		{
			GPIO_digitalWrite_1(CTL1);
		}
		else
		{
			GPIO_digitalWrite_0(CTL1);
		}

		if (target_pin == 1)
		{
			GPIO_digitalWrite_1(CTL2);
		}
		else
		{
			GPIO_digitalWrite_0(CTL2);
		}

		if (target_pin == 2)
		{
			GPIO_digitalWrite_1(CTL3);
		}
		else
		{
			GPIO_digitalWrite_0(CTL3);
		}

		if (target_pin == 3)
		{
			GPIO_digitalWrite_1(CTL4);
		}
		else
		{
			GPIO_digitalWrite_0(CTL4);
		}

		if (target_pin == 4)
		{
			GPIO_digitalWrite_1(CTL5);
		}
		else
		{
			GPIO_digitalWrite_0(CTL5);
		}

		if (target_pin == 5)
		{
			GPIO_digitalWrite_1(CTL6);
		}
		else
		{
			GPIO_digitalWrite_0(CTL6);
		}

		if (target_pin == 6)
		{
			GPIO_digitalWrite_1(CTL7);
		}
		else
		{
			GPIO_digitalWrite_0(CTL7);
		}

		if (target_pin == 7)
		{
			GPIO_digitalWrite_1(CTL8);
		}
		else
		{
			GPIO_digitalWrite_0(CTL8);
		}

		if (target_pin == 8)
		{
			GPIO_digitalWrite_1(CTL9);
		}
		else
		{
			GPIO_digitalWrite_0(CTL9);
		}

		if (target_pin == 9)
		{
			GPIO_digitalWrite_1(CTL10);
		}
		else
		{
			GPIO_digitalWrite_0(CTL10);
		}

		if (target_pin >= PINS)
		{
			start_us = now_us;
		}
	}
}

int main()
{
	SystemInit();

	setup();

	main_loop();
}
