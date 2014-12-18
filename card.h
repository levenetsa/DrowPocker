#ifndef CARD_H
#define CARD_H

#include <string>

class human_player;
class game;

class card
{
public:
    int suit;
    int weight;
    card(int);
    card();
    ~card();
protected:
    card operator=(card const& h);
    friend game;
    friend human_player;
    std::string get_owner() const;
    std::string get_weight();
    std::string get_suit();
    std::string owner;
};


#endif // CARD_H

