#include "closed_card.h"






closed_card::~closed_card()
{

}


 closed_card::closed_card(){
 }
    closed_card::closed_card(int n){
         suit=n/13;
    weight=n%13;
    }

/*card::card(int n)
{
    suit=n/13;
    weight=n%13;
}*/
