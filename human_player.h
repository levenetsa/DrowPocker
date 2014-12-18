#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "game.h"
#include <string>

class game;

class human_player
{
public:
    human_player();
    human_player(int, std::string);
    ~human_player();
    std::string get_name();
    int get_balance();
    card* get_cards(card * h);
    int get_size(card * h);
    friend game;
protected:
    std::string name;
    int balance;
private:


};


#endif // HUMAN_PLAYER_H

