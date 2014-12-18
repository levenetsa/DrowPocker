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
    friend game;
    friend human_player;
    friend vector.tcc;
    //friend card(std::string,card const& h);

protected:
    card operator=(card const& h);
    std::string get_owner() const;
    std::string get_weight();
    std::string get_suit();
    std::string owner;
private:
};


#endif // CARD_H

