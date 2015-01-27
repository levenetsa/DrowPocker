#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "game.h"
#include <string>
#include "player.h"

class game;

class human_player:player
{
public:
    human_player();
    //constructor for players where
    //balance; name
    human_player(int, std::string);
    //init player money:name
    ~human_player();
protected:
    std::string get_name();
    int get_balance();
    card * get_cards(card * h);
    int get_size(card * h);
    friend class game;
};


#endif // HUMAN_PLAYER_H

