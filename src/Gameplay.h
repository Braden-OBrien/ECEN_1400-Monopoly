// Gameplay.h

#ifndef _GAMEPLAY_h
#define _GAMEPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MonopolyFunctions.h"

void PlayGame();

#endif