// 
// 
// 

#include "MonopolyFunctions.h"

int Roll(int i)
{
    Serial.println("Inside Rolling");
    std::string output = "Press A to roll!";
    bool input = false;
    lcd_write(i, output, 0, 0);
    while (!input) { input = digitalRead(Players[i].buttons[0]); }
    bool isDouble = false;
    isDouble = Players[i].Move();
    delay(2000);
    return isDouble;
}

void Buy(int i)
{
    std::ostringstream output;
    if (Players[i].money - Players[i].position->Price > 0)
    {
        bool input = false;
        output << "Would you like to buy " << Players[i].position->Name << "? (y/n)";
        lcd_write(i, output.str(), 0, 0);
        while (!input) { input = digitalRead(Players[i].buttons[0]) || digitalRead(Players[i].buttons[1]); }
        std::ostringstream output1;
        if (digitalRead(Players[i].buttons[0]))
        {
            *Players[i].position->Owner = i;
            Players[i].money -= Players[i].position->Price;
            output1 << "You've bought " << Players[i].position->Name << "!";
        }
        else {
            output1 << "You decided to not buy " << Players[i].position->Name << ".";
        }
        lcd_write(i, output1.str(), 0, 0);
    }
    else {
        output << "You can't afford this property.";
        lcd_write(i, output.str(), 0, 0);
    }
}

void Effects(int i)
{
    std::string name = Players[i].position->Name;
    bool input = false;
    if (name == "Chance")
    {
        std::string output = "Time to draw a chance card! Press A!";
        lcd_write(i, output, 0, 0);
        while (!input) { input = digitalRead(Players[i].buttons[0]); }
        Players[i].Chance();
    }
    else if (name == "GO TO JAIL")
    {
        Players[i].GOTO();
    }
    else if (name == "Community Chest")
    {
        std::string output = "Time to draw a card from the Community Chest! Press A!";
        lcd_write(i, output, 0, 0);
        while (!input) { input = digitalRead(Players[i].buttons[0]); }
        Players[i].CommunityChest();
    }
}

void JailCheck(int i, bool* reroll)  //If the player is in jail, run the function MAKE THIS A BOOL AND ADDS 1 TO REROLL IF TRUE!!
{
    std::string output;
    output.clear();
    bool input = false;
    if (Players[i].jail_c > 3) {
        output = "You've spent too long in Jail. Time to pay up! Press A to pay $50!";
        lcd_write(i, output, 0, 0);
        while (!input) { input = digitalRead(Players[i].buttons[0]); }
        Players[i].money -= 50;
        Players[i].jail_c = 0;
        *reroll = true;
    }
    else {
        output = "You're in jail! Press A to roll the dice, or press B to pay the price!";
        lcd_write(i, output, 0, 0);
        while (!input) { input = (digitalRead(Players[i].buttons[0]) || digitalRead(Players[i].buttons[1])); } 
        int user_input = digitalRead(Players[i].buttons[0]);
        Players[i].Jail(user_input, reroll);
    }
}
