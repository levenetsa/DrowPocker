#include "closed_card.h"

closed_card::~closed_card(){}

closed_card::closed_card(){}

closed_card::closed_card(int n){
    //suit
    suit=n/13;
    //weight
    weight=n%13;
}
