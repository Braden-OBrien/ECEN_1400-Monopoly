// Monopoly.h

#ifndef _MONOPOLY_h
#define _MONOPOLY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Scripts.h"
#include <time.h>
#include <sstream>

class Tile {
public:
    std::string Name;
    int* Owner;
    int Rent;
    int Price;

    Tile(std::string name, int* owner, int rent, int price);

    Tile() {};

private:
    int owner_ = -1;
};

class Player {
public:
    int player_id;  //Players array index of the player
    int money = 1500;
    Tile* position;  //The position tile of the player
    int position_n = 0;  //Tiles array index of the player's position
    int dice_n;  //The value of the dice roll
    int doubles_c = 0;  //Tells the number of doubles a player has rolled in succession.
    int jail_c = 0;  //Tells the number of turns a player has spent in jail.
    int buttons[2];

    void doMoney();

    int diceRoll(bool* isDouble) // Dice Rolling Function
    {
        *isDouble = false;
        Serial.println("Inside of diceRoll");
        Serial.print("Double is :");
        Serial.println(*isDouble);
        //randomSeed(millis());
        randomSeed(analogRead(A0));
        int rng = random(1, 22);
        Serial.print("rng is: ");
        Serial.println(rng);
        if (rng == 1) { dice_n = 2; *isDouble = true; }
        else if (rng == 2) { dice_n = 3; }
        else if (rng < 5) {
            dice_n = 4;
            if (rng == 4) {
                *isDouble = true;
            }
        }
        else if (rng < 7) {
            dice_n = 5;
        }
        else if (rng < 10) {
            dice_n = 6;
            if (rng == 9) {
                *isDouble = true;
            }
        }
        else if (rng < 13) {
            dice_n = 7;
        }
        else if (rng < 16) {
            dice_n = 8;
            if (rng == 15) {
                *isDouble = true;
            }
        }
        else if (rng < 18) {
            dice_n = 9;
        }
        else if (rng < 20) {
            dice_n = 10;
            if (rng == 19) {
                *isDouble = true;
            }
        }
        else if (rng == 20) { dice_n = 11; }
        else if (rng == 21) { dice_n = 12; *isDouble = true; }
        Serial.println("End of diceRoll");
        Serial.print("double is: ");
        Serial.println(*isDouble);
        return dice_n;

        //1 way for 2  //1
        //1 ways for 3  //2
        //2 ways for 4 //4
        //2 ways for 5  //6
        //3 ways for 6  //9
        //3 ways for 7  //12
        //3 ways for 8  //15
        //2 ways for 9  //17
        //2 ways for 10  //19
        //1 ways for 11  //20
        //1 ways for 12  //21
        //21 possible rolls
    }

    int doMove(int diceRoll) {
        Serial.println("Inside doMove");
        int n_prev = int{ position_n };
        position_n += diceRoll;
        return n_prev;
    }

    bool Move();

    int Move(int _val);

    void GOTO();

    void Jail(int input, bool* reroll);

    void Chance();

    void CommunityChest();

    Player(int id_);

    Player() {};
};

extern Player Players[4];

void StartLEDs();

#endif