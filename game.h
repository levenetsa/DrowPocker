#ifndef GAME_H
#define GAME_H

#include <string>
#include "card.h"
#include "closed_card.h"
#include "open_card.h"
#include "human_player.h"
#include <cstdlib>
#include <ctime>

class human_player;

class game
{
public:
    game();
    game (int,int,std::string[]);
    void run();
    ~game();

protected:
    bool check();
    bool small_check();
    void init_players();
    void shake_cards();
    void init_money(bool);
    void round(bool);
    void share(int[],int);
    void show_down();
    void second_round();
    void after_card_give();
    void drop_cards(bool,int, std::string);
    bool call_check(int, std::string, std::string);
    friend human_player;
    int sbalance;
    int player_amount;
    std::string * names;
    card cards[52];
    int* after_card_getting;
    human_player * gplayers;
    int banck;
    int diller;
    int * putts;
    bool * player_possibility;
    int rised;
    bool* folded;
    int glob_card_pointer;
private:

    void start();
};

    double kikker(card* cards);
    double couple(card* cards);
    double double_couple(card* cards);
    double triple(card* cards);
    double strit(card* cards);
    double flesh(card* cards);
    double full_house(card* cards);
    double kare(card* cards);
    double strit_flesh(card* cards);
#endif // GAME_H

