/*
 * KeyAndLed.c
 *
 * Created: 19/02/2024 11.22.36
 * Author : himal
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "led_driver.h"
#include "key_input_driver.h"
#include "LogicOperation.h"

int main(void)
{
	init_Application();
    /* Replace with your application code */
    while (1) 
    {
		run_Operators();
		_delay_ms(400);
    }
}

