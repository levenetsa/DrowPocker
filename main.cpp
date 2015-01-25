#include <iostream>
#include "card.h"
#include "closed_card.h"
#include "game.h"
#include <string>
using namespace std;

int main()
{
    std::string names[]={"Sania","Alex","Vasia"};
    game g=game(300,3,names);
    g.run();
    //game (int,int,std::string[]);
    return 0;
}
