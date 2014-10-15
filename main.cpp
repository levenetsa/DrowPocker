#include <iostream>
#include "closed_card.h"

using namespace std;

int main()
{
    card a[52];
    for (int i=0;i<52 ;i++ )
        a[i]= card(i);
    cout << "End" << endl;
    return 0;
}
