#ifndef CLOSED_CARD_H
#define CLOSED_CARD_H
#include "card.h"

class closed_card
{

public:
    int suit;
    int weight;
    closed_card(card const& n);
    ~closed_card();
protected:
private:
};


#endif // CLOSED_CARD_H
