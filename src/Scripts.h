// Scripts.h

#ifndef _SCRIPTS_h
#define _SCRIPTS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ArduinoSTL.h>
#include <FastLED.h>
#include <string>
#include <vector>

namespace scripts
{
	static const int lcd_length = 20;
	static const int lcd_height = 4;

	static const int led_count = 144;
	static const int data_pin = 3;

	static const int boardSize = 36;

	static const int buttons[8] = 
	{
		7,
		6,
		8,
		9,
		10,
		11,
		13,
		12
	};

	static CRGB colors[4] = {
	CRGB::Green,
	CRGB::Red,
	CRGB::Blue,
	CRGB::Purple
	};

	static CRGB leds[led_count];

	void InitializeLEDs();

	void InitializeLCDs();

	void cursor_set(int lcd_id, int x, int y);

	void string_split(std::string outputs[4], std::string message, int x);

	void led_toggle(int led_id, CRGB color);
}

void led_move(int n_start, int n, int player_id);
void led_move_backwards(int n_start, int n, int player_id);
void lcd_write(int lcd_id, std::string message, int x, int y);

#endif