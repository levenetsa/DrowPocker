#include "card.h"
#include <cstdlib>

card::card()
{

}

card card::operator=(card const& h)
{
    suit=h.suit;
    weight=h.weight;
    owner=h.owner;
    return *this;
}

std::string card::get_owner() const
{
    return owner;
}

std::string card::get_weight()
{
    std::string w_str[]={"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

    return w_str[weight];
}

std::string card::get_suit()
{
    card k;
    k = (*this);
    std::string suits[]= {"_Kre", "_Bub", "_Che", "_Pik"};
    //std::string suits[]= {"♣", "♦", "♥", "♠"};
//    int siu=suit;
    std::string s=suits[suit];
    return suits[suit];
}

card::~card()
{

}

card::card(int n)
{
    suit=n/13;
    weight=n%13;
}
