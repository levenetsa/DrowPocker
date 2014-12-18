#include "open_card.h"


    open_card::open_card(){}

    open_card::~open_card(){}

    open_card::open_card(int n){
        suit=n/13;
    weight=n%13;
    }
    open_card::open_card(std::string name,card const& h){
        owner=name;
        suit=h.suit;
    weight=h.weight;
    }

