#include "open_card.h"

open_card::open_card(){}

open_card::~open_card(){}

open_card::open_card(int n){
    //suit
    suit = n/13;
    //weight
    weight = n%13;
}

open_card::open_card(std::string name, card const& h){
    //owner
    owner = name;
    //suit
    suit = h.suit;
    //weight
    weight = h.weight;
}

