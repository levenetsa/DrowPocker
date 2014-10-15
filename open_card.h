#ifndef OPEN_CARD_H
#define OPEN_CARD_H
#include "closed_card.h"
class open_card
{
    int suit;
    int weight;
public:
    open_card(closed_card card);
    ~open_card();
protected:
private:
};


#endif // OPEN_CARD_H
