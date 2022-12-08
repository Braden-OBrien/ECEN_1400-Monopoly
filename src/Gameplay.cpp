// 
// 
// 

#include "Gameplay.h"

void PlayGame()
{
    for (int i = 0; i < 4; i++)
    {
        bool reroll = false;
        std::ostringstream output;
        output << "You're player " << i + 1 << ". Your turn!";
        lcd_write(i, output.str(), 0, 0);
        Serial.println("Printed!");
        delay(3000);
        if (Players[i].jail_c > 0)
        {
            JailCheck(i, &reroll);
        }
        else
        {
            Serial.println("Rolling");
            if (Roll(i))
            {
                Serial.println("Rolling Complete");
                reroll = true;
                Players[i].doubles_c++;
                if (Players[i].doubles_c == 3)
                {
                    std::ostringstream output1;
                    output1 << "Wow! Another double! Bust! Go to Jail!";
                    lcd_write(i, output1.str(), 0, 0);
                    Players[i].GOTO();
                    continue;
                }
                std::ostringstream output2;
                output2 << "You've rolled a double!";
                lcd_write(i, output2.str(), 0, 0);
            }
        }
        if (Players[i].position->Owner != NULL) {
            if (*Players[i].position->Owner == -1) {
                Serial.println("Buying!");
                Buy(i);
                Serial.print("Owned by Player: ");
                Serial.println((*Players[i].position->Owner) + 1);
            }
            else {
                Serial.println("Money Doin");
                Players[i].doMoney();
            }
        }
        else {
            Serial.println("Effects n shit");
            Effects(i);
        }
        std::ostringstream output3;
        if (!reroll)
        {
            output3 << "Your turn is over! You have $" << Players[i].money << ".";
        }
        else {
            output3 << "You have $" << Players[i].money << "." << " Go again!";
        }
        lcd_write(i, output3.str(), 0, 0);
        if (reroll)
        {
            Serial.println("Going again");
            i -= 1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        Players[i].doubles_c = 0;
    }
}
