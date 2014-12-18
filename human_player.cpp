#include "human_player.h"
#include <vector>

human_player::human_player(){};

human_player::~human_player()
{

}
human_player::human_player(int b, std::string n){
    name=n;
    balance=b;
}
    std::string human_player::get_name()
    {
        return name;
    }

    int human_player::get_balance(){
        return balance;
    }


    card * human_player::get_cards(card * h)
    {
        std::vector<card> l_cards;
        std::string player_name=get_name();
        for (int i=0; i<52; i++)
            if (player_name==h[i].get_owner())
            {
                l_cards.push_back(h[i]);
            }
        card* m_cards=new card[l_cards.size()];
        for (unsigned int i=0; i<l_cards.size(); i++)
            m_cards[i]=l_cards[i];
        return m_cards;
    }

    int human_player::get_size(card * h)
    {
        int j=0;
        std::string player_name=get_name();
        for (int i=0; i<52; i++)
            if (player_name==h[i].get_owner())
            {
                j++;
            }
        return j;
    }
