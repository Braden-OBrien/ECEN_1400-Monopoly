// 
// 
// 

#include "Monopoly.h"

Player Players[4] = {
    Player(0),
    Player(1),
    Player(2),
    Player(3)
};

Tile _jail = Tile("Jail", nullptr, 0, 0);

Tile Tiles[36] = {
    Tile("GO", nullptr, -200, 0),
    Tile("Mediterranean Avenue", nullptr, 2, 60),
    Tile("Community Chest", nullptr, 0, 0),
    Tile("Baltic Avenue", nullptr, 2, 60),
    Tile("Reading Railroad", nullptr, 25, 200),
    Tile("Oriental Avenue", nullptr, 6, 100),
    Tile("Chance", nullptr, 0, 0),
    Tile("Vermont Avenue", nullptr, 6, 100),
    Tile("Connecticut Avenue", nullptr, 8, 120),
    Tile("Just Visiting", nullptr, 0, 0),
    Tile("St.Charles Place", nullptr, 10, 140),
    Tile("States Avenue", nullptr, 10, 140),
    Tile("Virginia Avenue", nullptr, 12, 160),
    Tile("Pennsylvania Railroad", nullptr, 25, 200),
    Tile("St.James Place", nullptr, 14, 180),
    Tile("Community Chest", nullptr, 0, 0),
    Tile("Tennesessee Avenue", nullptr, 14, 180),
    Tile("New York Avenue", nullptr, 16, 200),
    Tile("Free Parking", nullptr, 0, 0),
    Tile("Kentucky Avenue", nullptr, 18, 220),
    Tile("Chance", nullptr, 0, 0),
    Tile("Indiana Avenue", nullptr, 18, 220),
    Tile("Illinois Avenue", nullptr, 20, 240),
    Tile("B & O Railroad", nullptr, 0, 0),
    Tile("Atlantic Avenue", nullptr, 22, 260),
    Tile("Ventnor Avenue", nullptr, 22, 260),
    Tile("Marvin Gardens", nullptr, 24, 280),
    Tile("GO TO JAIL", nullptr, 0, 0),
    Tile("Pacific Avenue", nullptr, 26, 300),
    Tile("North Carolina Avenue", nullptr, 26, 300),
    Tile("Community Chest", nullptr, 0, 0),
    Tile("Pennsylvania Avenue", nullptr, 28, 320),
    Tile("Short Line Railroad", nullptr, 25, 200),
    Tile("Chance", nullptr, 0, 0),
    Tile("Park Place", nullptr, 35, 350),
    Tile("Board Walk", nullptr, 50, 400)
};

Tile::Tile(std::string name, int* owner, int rent, int price)
{
    Price = price;
    Name = name;
    if (price != 0)
    {
        Owner = &owner_;
    }
    Rent = rent;
}

Player::Player(int id_)
{
    position = &Tiles[0];
    player_id = id_;

    buttons[0] = scripts::buttons[id_ * 2];
    buttons[1] = scripts::buttons[(id_ * 2) + 1];

    pinMode(buttons[0], INPUT);
    pinMode(buttons[1], INPUT);
};

int Player::Move(int _val)
{
    int n_prev = doMove(_val);
    std::ostringstream output1;
    if (position_n > n_prev)
    {
        output1 << "You rolled " << position_n - n_prev << "!";
    }
    else {
        output1 << "You rolled " << (36 - n_prev + position_n) << "!";
    }
    lcd_write(player_id, output1.str(), 1, 1);
    delay(2000);
    led_move(n_prev, position_n, player_id);
    if (position_n > scripts::boardSize - 1)
    {
        position_n -= scripts::boardSize;
        money += 200;
        std::string output = "You've passed GO!";
        lcd_write(player_id, output, 1, 1);
    }
    Serial.print("Initial pos is: ");
    Serial.println(*position->Name.c_str());
    position = &Tiles[position_n];
    Serial.print("Updated position is: ");
    Serial.println(*position->Name.c_str());
    std::stringstream out;
    out.clear();
    out << "You've landed on " << position->Name << "!";
    lcd_write(player_id, out.str(), 0, 0);
    return 0;
}

bool Player::Move()
{
    bool isDouble = false;
    int n_prev = doMove(diceRoll(&isDouble));
    std::ostringstream output1;
    if (position_n > n_prev)
    {
        output1 << "You rolled " << position_n - n_prev << "!";
    }
    else {
        output1 << "You rolled " << (36 - n_prev + position_n) << "!";
    }
    lcd_write(player_id, output1.str(), 1, 1);
    delay(2000);
    led_move(n_prev, position_n, player_id);
    if (position_n > scripts::boardSize - 1)
    {
        position_n -= scripts::boardSize;
        money += 200;
        std::string output = "You've passed GO!";
        lcd_write(player_id, output, 1, 1);
        delay(2000);
    }
    position = &Tiles[position_n];
    std::stringstream out;
    out.clear();
    out << "You've landed on " << position->Name << "!";
    lcd_write(player_id, out.str(), 0, 0);
    return isDouble;
}

void Player::doMoney()
{
    std::ostringstream output;
    output.clear();
    if (*position->Owner != player_id)
    {
        money -= position->Rent;
        Players[*position->Owner].money += position->Rent;
        output << "You've payed $" << position->Rent << " in rent to Player " << *(position->Owner) + 1 << "!";
        lcd_write(player_id, output.str(), 0, 0);
    }
    else {
        output << "You own this tile. No rent for you!";
        lcd_write(player_id, output.str(), 0, 0);
    }
}

void Player::GOTO()
{
    std::string output = "You're going to jail!";
    lcd_write(player_id, output, 0, 0);
    scripts::led_toggle((Players[player_id].position_n * 4) + player_id, CRGB::Black);
    delay(500);
    position_n = 9;
    position = &_jail;
    jail_c++;
    scripts::led_toggle((Players[player_id].position_n * 4) + player_id, scripts::colors[player_id]);
}

void Player::Jail(int input, bool* reroll)
{
    std::ostringstream output;
    output.clear();
    if (!input)
    {
        output << "You've payed $50 to the bank.";
        lcd_write(player_id, output.str(), 0, 0);
        money -= 50;
        *reroll = true;
    }
    else {
        //randomSeed(millis());
        randomSeed(analogRead(A0));
        int rng = random(1, 22);
        if (rng == 1) {
            Move(2);
        }
        else if (rng == 2) {
            Move(4);
        }
        else if (rng == 3) {
            Move(6);
        }
        else if (rng == 4) {
            Move(8);
        }
        else if (rng == 5) {
            Move(10);
        }
        else if (rng == 6) {
            Move(12);
        }
        else {
            output << "You didn't get a double! You're staying in jail tonight.";
            lcd_write(player_id, output.str(), 0, 0);
            return;
        }
        output << "You've rolled double " << rng << "\'s!";
        lcd_write(player_id, output.str(), 0, 0);
    }
    jail_c = 0;
}

void Player::Chance()
{
    std::string output;
    //randomSeed(millis());
    randomSeed(analogRead(A0));
    int card = random(1, 11);
    if (card == 1)
    {
        output = "Bank pays you dividend of $50.";
        money += 50;
    }
    else if (card == 2)
    {
        output = "Advance to 'Go'. (Collect $200)";
        money += 200;
        position = &Tiles[0];
    }
    else if (card == 3)
    {
        output = "Go to Jail. Go directly to Jail. Do not pass GO, do not collect $200.";
        GOTO();
    }
    else if (card == 4)
    {
        output = "It is your birthday, collect $10 for every player.";
        money += 30;
    }
    else if (card == 5)
    {
        output = "Pay hospital fees of $100";
        money += -100;
    }
    else if (card == 6)
    {
        output = "Income tax refund. Collect $20.";
        money += 20;
    }
    else if (card == 7)
    {
        output = "Receive $25 consultancy fee";
        money += 25;
    }
    else if (card == 8)
    {
        output = "School Fee. Pay $25.";
        money += -25;
    }
    else if (card == 9)
    {
        output = "Advance to B & O Railroad.";
        if (position_n < 23)
        {
            led_move(position_n, 23, player_id);
        }
        else if (position_n > 23)
        {
            led_move_backwards(position_n, 23, player_id);
        }
        else { output = "You cannot advance to B & O Railroad."; }
        position_n = 23;
        position = &Tiles[position_n];
    }
    else
    {
        output = "You have won second prize in a beauty contest. Collect $10";
        money += 10;
    }
    lcd_write(player_id, output, 0, 0);
}

void Player::CommunityChest()
{
    std::string output;
    //randomSeed(millis());
    randomSeed(analogRead(A0));
    int card = random(1, 7);
    if (card == 1)
    {
        output = "Advance to Boardwalk.";
        scripts::led_toggle(position_n, CRGB::Black);
        position_n = 35;
        position = &Tiles[35];
        scripts::led_toggle(position_n, scripts::colors[player_id]);
    }
    else if (card == 2)
    {
        output = "Doctor's fee. Pay $50";
        money += -50;
    }
    else if (card == 3)
    {
        output = "Go back 2 spaces.";
        led_move_backwards(position_n, position_n - 2, player_id);
        position_n -= 2;
        position = &Tiles[position_n];
    }
    else if (card == 4)
    {
        output = "From sale of stock you get $50";
        money += 50;
    }
    else if (card == 5)
    {
        output = "Holiday fund matures. Receive $100";
        money += 100;
    }
    else if (card == 6)
    {
        output = "Speeding fine $15.";
        money += -15;
    }
    else
    {
        output = "Income tax refund. Collect $20";
        money += 20;
    }
    lcd_write(player_id, output, 0, 0);
}

void StartLEDs()
{
    for (int i = 0; i < 4; i++)
    {
        scripts::led_toggle(i, scripts::colors[i]);
    }
}