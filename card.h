#ifndef CARD_H
#define CARD_H

#include <string>

class human_player;
class game;

class card
{
public:
    //suit
    int suit;
    //weight
    int weight;
    //card constructor from int where int / 13 = suit
    //and int % 13 = weight
    card(int);
    card();
    ~card();
protected:
    card operator=(card const& h);
    friend class game;
    friend class human_player;
    std::string get_owner() const;
    std::string get_weight();
    std::string get_suit();
    std::string owner;
};


#endif // CARD_H

