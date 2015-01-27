#ifndef OPEN_CARD_H
#define OPEN_CARD_H

#include "closed_card.h"
#include <string>
#include "card.h"

class closed_card;

class open_card: public card
{
public:
    //open card constructor from int where string is owner;
    //int / 13 = suit and int % 13 = weight
    open_card(std::string,card const& h);
    //constructors
    open_card(int);
    open_card();
    //copyconstructor
    open_card(const open_card&);
    ~open_card();
protected:
private:
};


#endif // OPEN_CARD_H
