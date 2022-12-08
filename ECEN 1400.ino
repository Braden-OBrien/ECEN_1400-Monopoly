// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       ECEN 1400.ino
    Created:	11/16/2022 1:30:40 PM
    Author:     LAPTOP-EB1CNADT\BLO20
*/



#include <aaaaaaaaa.h>
#include "Gameplay.h"
#include <HID.h>
#include <ArduinoSTL.h>
#include <Wire.h>
#include <FastLED.h>

void setup()
{
    pinMode(A0, INPUT);
    randomSeed(analogRead(A0));
    Serial.begin(9600);
    scripts::InitializeLEDs();
    StartLEDs();
    scripts::InitializeLCDs();
}

// Add the main program code into the continuous loop() function
void loop()
{
    PlayGame();
}
