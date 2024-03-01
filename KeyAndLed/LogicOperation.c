/*
 * LogicOperation.c
 *
 * Created: 01/03/2024 09.36.39
 *  Author: himal
 */ 

#include "LogicOperation.h"
#include "led_driver.h"
#include "key_input_driver.h"

void init_Application() {
	init_leds();
	init_keys();
}

void run_Operators() {
	bool key1 = get_key(1);
	bool key2 = get_key(2);

	// Logic 
	
	// AND  and NAND
	if (key1 && key2) 
	{
		set_led(1, 1);
		set_led(4, 0);
	}
	else
	{
		set_led(1, 0);
		set_led(4, 1);
	}

	//OR and NOR
	if (key1 || key2 ) 
	{
		set_led(2, 1);
		set_led(5, 0);
	}
	else
	{
		set_led(2, 0);
		set_led(5, 1);
	}

	// XOR and XNOR
	if (key1 ^ key2)
	{
		set_led(3, 1);
		set_led(6, 0);
	}
	else
	{
		set_led(3, 0);
		set_led(6, 1);
	}

}