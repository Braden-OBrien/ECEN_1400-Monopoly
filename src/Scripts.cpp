// 
// 
// 


//Buttons 13-6

#include <Wire.h>
#include "aaaaaaaaa.h"
#include "Scripts.h"

using namespace std;
using namespace scripts;

LiquidCrystal_I2C LCDS[4]
{
  LiquidCrystal_I2C(0x27, lcd_length, lcd_height),  //Corresponds to Player 1
  LiquidCrystal_I2C(0x26, lcd_length, lcd_height),  //2
  LiquidCrystal_I2C(0x25, lcd_length, lcd_height),  //3
  LiquidCrystal_I2C(0x23, lcd_length, lcd_height)   //4
};

namespace scripts
{
    void InitializeLCDs()
    {
        for (int i = 0; i < 4; i++)
        {
            LCDS[i].init();
            LCDS[i].backlight();
            LCDS[i].begin(20, 4);
            LCDS[i].leftToRight();
        }
    }

    void cursor_set(int lcd_id, int x, int y)
    {
        if ((x < lcd_length) && (x >= 0) && (y < lcd_height) && (y >= 0))
        {
            LCDS[lcd_id].setCursor(x, y);
        }
        else {
            Serial.println("Invalid Cursor Address");
            Serial.print("X is ");
            Serial.println(x);
            Serial.print("Y is ");
            Serial.println(y);
        }
    }

    void string_split(string outputs[4], string message, int x)  //Split a string into multiple shorter strings of defined length
    {
        int length = message.length();
        Serial.println(length);
        for (int i = x; i < length; i++)
        {
            if (i < 20)
            {
                outputs[0].push_back(message.at(i));
                //Serial.println(outputs[0].c_str());
            }
            else if (i < 40)
            {
                outputs[1].push_back(message.at(i));
                //Serial.println(outputs[1].c_str());
            }
            else if (i < 60)
            {
                outputs[2].push_back(message.at(i));
                //Serial.println(outputs[2].c_str());
            }
            else if (i < 80)
            {
                outputs[3].push_back(message.at(i));
                //Serial.println(outputs[3].c_str());
            }
            else {
                return;
            }
        }
    }

    void InitializeLEDs()
    {
        FastLED.addLeds<NEOPIXEL, data_pin>(leds, led_count);
        FastLED.addLeds<WS2812, data_pin, RGB>(leds, led_count);
    }

    void led_toggle(int led_id, CRGB color)
    {
        leds[led_id] = color;
        FastLED.show();
        delay(250);
    }
}

void lcd_write(int lcd_id, string message, int x, int y)
{
    Serial.print("Printing: ");
    Serial.println(message.c_str());
    LCDS[lcd_id].command(LCD_CLEARDISPLAY);
    delay(2000);
    string strings[4];
    string_split(strings, message, x);
    for (int i = y; i < 4; i++)
    {
        if (strings[i].c_str() != "")
        {
            LCDS[lcd_id].setCursor(x, i);
            LCDS[lcd_id].printstr(strings[i].c_str());
            Serial.println(strings[i].c_str());
        }
    }
    delay(2000);
}

void led_move(int n_start, int n, int player_id)
{
    Serial.println("In led_move");
    Serial.print(n_start);
    Serial.print(", ");
    Serial.print(n);
    Serial.print(", ");
    Serial.println(player_id);
    if (n < boardSize)
    {
        for (int i = n_start; i != n; i++)
        {
            int led_id = (4 * i) + player_id;
            led_toggle((4 * i) + player_id, CRGB::Black);
            led_toggle((4 * (i + 1)) + player_id, colors[player_id]);
        }
    }
    else
    {
        for (int i = n_start; i != n; i++)
        {
            if (i < boardSize)
            {
                int led_id = (4 * i) + player_id;
                led_toggle((4 * i) + player_id, CRGB::Black);
                led_toggle((4 * (i + 1)) + player_id, colors[player_id]);
            }
            else {
                int j = i - 12;
                int led_id = (4 * j) + player_id;
                led_toggle((4 * j) + player_id, CRGB::Black);
                led_toggle((4 * (j + 1)) + player_id, colors[player_id]);
            }
        }
    }
}

void led_move_backwards(int n_start, int n, int player_id)
{
    if (n > -1)
    {
        for (int i = n_start; i != n; i--)
        {
            int led_id = (4 * i) + player_id;
            led_toggle((4 * i) + player_id, CRGB::Black);
            led_toggle((4 * (i - 1)) + player_id, colors[player_id]);
        }
    }
    else
    {
        for (int i = n_start; i != n; i--)
        {
            if (i > -1)
            {
                int led_id = (4 * i) + player_id;
                led_toggle((4 * i) + player_id, CRGB::Black);
                led_toggle((4 * (i - 1)) + player_id, colors[player_id]);
            }
            else {
                int j = i + boardSize;
                int led_id = (4 * j) + player_id;
                led_toggle((4 * j) + player_id, CRGB::Black);
                led_toggle((4 * (j - 1)) + player_id, colors[player_id]);
            }
        }
    }
}

/*LCDS[lcd_id].command(LCD_CLEARDISPLAY);
    delay(50);
    LCDS[lcd_id].setCursor(x, y);
    LCDS[lcd_id].printstr(message.c_str());*/


    /*LCDS[lcd_id].clear();
    delay(50);
    vector<string> new_strings;
    new_strings.push_back(message);
    if (message.length() > (lcd_length - x))  //Too large for the row?
    {
        for (int c = y - 3; c != 0; c++)  //Reduce the size, if all the rows are done
        {
            new_strings = scripts::string_split(new_strings, x);
            if (new_strings.back().length() < (lcd_length - x)) //or the size is ok, break
            {
                break;
            }
        }
        if (new_strings.back().length() > (lcd_length - x)) //Too many plain bagels
        {
            //Serial.println("String too large for LCD Display");
            return;
        }
    }
    for (int c = y; y != lcd_height; y++)
    {
        scripts::cursor_set(lcd_id, x, c);
        LCDS[lcd_id].printstr(new_strings.at(c).c_str());  //Printing to LCD
    }
    delay(2000);*/

    /*string split;                                               //Separate into multiple strings
            string message = strings.back();
            char _first = message.front();
            strings.erase(strings.end() - 1);
            while (split.length() < (lcd_length + 1 - x) || message.length() == 0)
            {
                if (((message.front() == _first) && (_first == ' ')) && split.length() == 0)    //Remove spaces at the beginning of a new line
                {
                    message.erase(message.begin());
                    continue;
                }
                split.push_back(message.front());
                message.erase(message.begin());
            }
            strings.push_back(split);
            strings.push_back(message);
            return strings;*/