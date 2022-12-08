// MonopolyFunctions.h

#ifndef _MONOPOLYFUNCTIONS_h
#define _MONOPOLYFUNCTIONS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Monopoly.h"

int Roll(int i);
void Buy(int i);
void Effects(int i);
void JailCheck(int i, bool* reroll);

#endif

