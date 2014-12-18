#ifndef OPEN_CARD_H
#define OPEN_CARD_H

#include "closed_card.h"
#include <string>
#include "card.h"

class closed_card;

class open_card: public card
{
public:
     open_card(std::string,card const& h);
    open_card(int);
    open_card();
    open_card(const open_card&);
    ~open_card();
protected:
private:
};


#endif // OPEN_CARD_H
