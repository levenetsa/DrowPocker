#include "card.h"

card::~card()
{

}

card::card(int n)
{
    suit=n/13;
    weight=n%13;
}
