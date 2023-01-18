/*
 * led.c
 *
 *  Created on: Jan 18, 2023
 *      Author: User
 */
#include "stm32l4xx_hal.h"

#define LED_ON 		1
#define LED_OFF 	0

typedef struct {
	uint32_t time_on;
	uint32_t time_off;
	GPIO_TypeDef* port;
	uint32_t pin;
	uint32_t status;
	uint32_t start_tick;
} led_t;


led_t led_arr[] =
{
	{5000, 1000, GPIOB, GPIO_PIN_13, 1, 0},
	{1000, 1000, GPIOA, GPIO_PIN_5, 1, 0}

};

static void led_driver(led_t *led);

void led_init(void)
{

}

void led_main_function(void)
{
	for (uint8_t i = 0; i < sizeof(led_arr)/sizeof(led_t); i++)
	{
		led_driver(&led_arr[i]);
	}
}

/*
 * Function name: led_driver
 * Brief: This function help to control leds
 * Params[1]: led_t *led
 * Return: void
 */
static void led_driver(led_t *led)
{
	// Check if led is On or Off
	if(led->status == LED_ON)
	{
		// Event when turn off led
		if((HAL_GetTick() - led->start_tick) >= led->time_on)
		{
			HAL_GPIO_WritePin(led->port, led->pin, 1);
			led->status = LED_OFF;
		}
	}
	else
	{
		if((HAL_GetTick() - led->start_tick - led->time_on) >= led->time_off)
		{
			HAL_GPIO_WritePin(led->port, led->pin, 0);
			led->status = LED_ON;
			led->start_tick = HAL_GetTick();
		}
	}
}
