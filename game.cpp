#include "game.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <algorithm>

game::game() {}

game::~game() {}

game::game(int b, int am, std::string s[])
{
    //initing game
    //balance
    sbalance = b;
    //amount of players
    player_amount = am;
    //names
    names = s;
}


void game::run()
{
    //init diller
    diller = 0;
    //creating players
    init_players();
    //start rounds unless only one player will haven't 0 balance
    while(check())
    {
        //two money init condition
        //for first and second rounds
        init_money(true);
        shake_cards();
        //initing money and shaking cards
        //first round
        round(true);
        // two rounds for first true for second false
        after_card_give();
        // give card to player player if he dropped it
        std::cout << std::endl << "First Round is finished!" << std::endl <<
                  "Enter any key to begin Second Round" << std::endl;
        std::string s;
        std::cin >> s;
        //clearing screen
        system("cls");
        int m = 0;
        //amount of players with money
        for(int i = 0; i < player_amount; i++)
        {
            if (!folded[i] && gplayers[i].get_balance() != 0)
                m++;
        }
        //case for losing whole money in first round
        if (m > 1)
        {
            //reinit money
            //also two cases for first and second round
            init_money(false);
            //second round
            round(false);
        }
        std::cout << std::endl << "Second Round is finished!" << std::endl;
        std::cout << "Players' cards and rpeveous balances:" << std::endl;
        //information for players
        for (int tmp = 0; tmp < player_amount; tmp++)
        {
            card * player_cards = gplayers[tmp].get_cards(cards);
            int size = gplayers[tmp].get_size(cards);
            std::string s_cards = "";
            card k;
            for ( int i = 0; i < size ; i++ )
            {
                k = player_cards[i];
                s_cards += k.get_weight();
                s_cards += k.get_suit();
                s_cards += " ";
            }
            std::cout << gplayers[tmp].get_name() << "  " << s_cards << " " << gplayers[tmp].get_balance() << std::endl;
            delete[] player_cards;
        }
        //counting results
        show_down();
        std::cout << "Players' balances after check:" << std::endl;
        for (int tmp = 0; tmp < player_amount; tmp++)
        {
            std::cout << gplayers[tmp].get_name() << "  " << gplayers[tmp].get_balance() << std::endl;
        }
        std::cout << "Enter any key to continue" << std::endl;
        std::cin >> s;
        //next game begin if we don't have winner
        system("cls");
    }
    std::cout << std::endl << "Game Over" << std::endl;
}

bool game::check()
{
    std::vector<human_player> tmp_players;
    int tmp = 0;
    for (int i = 0; i < player_amount; i++)
        if (gplayers[i].balance != 0)
        {
            tmp_players.push_back(gplayers[i]);
            tmp++;
        }
    if (tmp == 1)
        return false;
    player_amount = tmp;
    tmp = tmp_players.size();
    human_player* t_players = new human_player[tmp];
    for(int i = 0; i < tmp; i++)
        t_players[i] = tmp_players[i];
    if (!gplayers) delete[] gplayers;
    gplayers = t_players;
    return true;
}

bool game::small_check()
{
    int fold = 0;
    for (int i = 0; i < player_amount; i++)
        if (folded[i]) fold++;
    if (fold == player_amount - 1) return false;
    for (int i = 0; i < player_amount; i++)
        if (putts[i] != rised && gplayers[i].get_balance() != 0 && !folded[i]) return true;
    return false;
}


void game::after_card_give()
{
    std::string p_name;
    for (int i = 0; i < player_amount; i++)
        if(!folded[i])
        {

            for(int j = 0; j < after_card_getting[i]; j++)
            {
                p_name = gplayers[i].get_name();
                cards[glob_card_pointer].owner = p_name;
                glob_card_pointer++;
            }
        }
}

double mass[32];
void game::show_down()
{

    mass[0] = 1;
    double c = 16;
    for (int i = 1; i < 32; i++)
    {
        mass[i] = c * mass[i - 1];
    }
    double result[10];
    for (int i = 0; i < player_amount; i++)
    {
        card* card_on_ceck = gplayers[i].get_cards(cards);

        result[i] = 0;
        result[i] += kikker(card_on_ceck);
        result[i] += couple(card_on_ceck);
        result[i] += double_couple(card_on_ceck);
        result[i] += triple(card_on_ceck);
        result[i] += strit(card_on_ceck);
        result[i] += flesh(card_on_ceck);
        result[i] += full_house(card_on_ceck);
        result[i] += kare(card_on_ceck);
        result[i] += strit_flesh(card_on_ceck);
        delete[] card_on_ceck;
    }
    double maxx = -1;
    int m_am = 1;
    int coun = 0;
    int fold = 0;
    int num = -1;
    int money_p = 0;
    for (int i = 0; i < player_amount; i++)
        if(folded[i]) fold++;
        else num = i;
    if (fold == player_amount - 1)
    {
        for (int i = 0; i < player_amount; i++)
            if (i != num) money_p += putts[i];
        gplayers[num].balance += money_p + putts[num];
        return;
    }
    while (coun != player_amount)
    {
        for (int i = 0; i < player_amount; i++)
            if (result[i] >= maxx)
            {
                if (result[i] == maxx) m_am++;
                else
                {
                    maxx = result[i];
                    m_am = 1;
                }
            }
        int am[10];
        int j = 0;
        for (int i = 0; i < player_amount; i++)
            if (result[i] == maxx)
            {
                result[i] = 0;
                am[j] = i;
                j++;
            }
        share(am, m_am);
        coun += m_am;
    }
    for(int i = 0; i < player_amount; i++)
        gplayers[i].balance += putts[i];
}

void game::share(int puts[], int size)
{
    int min = putts[puts[0]];
    int checker = 1;
    while (checker != 0)
    {
        for(int i = 1; i < size; i++)
            if (putts[puts[i]] < min)
            {
                min = putts[puts[i]];
                //          flag=puts[i];
            }
        int money = 0;
        for(int i = 0; i < player_amount; i++)
            if (putts[i] < min)
            {
                money += putts[i];
                putts[i] = 0;
            }
            else
            {
                putts[i] -= min;
                money += min;
            }
        money = money / size;
        for(int i = 0; i < size; i++)
            gplayers[puts[i]].balance += money;
        checker = 0;
        for(int i = 0; i < size; i++)
            if (putts[puts[i]] != 0)
                checker++;
    }
}

double kikker(card* cards)
{
    double return_am = 0;
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    std::sort(wet, wet + 5);
    for(int i = 0; i < 5; i++)
        return_am += wet[i] * mass[i];
    return return_am;
}

double couple(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    double return_am = 0;
    int maxx = -1;
    int x = -1, y = -1;
    for(int i = 0; i < 5; i++)
        for(int j = i + 1; j < 5; j++)
            if (wet[i] == wet[j] && maxx < wet[j])
            {
                maxx = wet[j];
                x = i;
                y = j;
            }
    int wet_nw[3];
    int j = 0;
    for(int i = 0; i < 5; i++)
    {
        if (i != x && i != y)
        {
            wet_nw[j] = wet[i];
            j++;
        }
    }
    if (maxx == -1) return 0;
    std::sort(wet_nw, wet_nw + 3);
    return_am += maxx * mass[8];
    return_am += wet_nw[2] * mass[7];
    return_am += wet_nw[1] * mass[6];
    return_am += wet_nw[0] * mass[5];
    return return_am;
}

double double_couple(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    double return_am = 0;
    int maxx = -1;
    int x = 0, y = 0;
    for(int i = 0; i < 5; i++)
        for(int j = i + 1; j < 5; j++)
            if (wet[i] == wet[j] && maxx < wet[j])
            {
                maxx = wet[j];
                x = i;
                y = j;
            }
    int wet_nw[3];
    int j = 0;
    for(int i = 0; i < 5; i++)
    {
        if (i != x && y != i)
        {
            wet_nw[j] = wet[i];
            j++;
        }
    }
    if (maxx == -1) return 0;
    int maxx2 = maxx;
    maxx = -1;
    for(int i = 0; i < 3; i++)
        for(int j = i + 1; j < 3; j++)
            if (wet_nw[i] == wet_nw[j] && maxx < wet_nw[j])
            {
                maxx = wet_nw[j];
            }
    if (maxx == -1) return 0;
    return_am += maxx * mass[10];
    return_am += maxx2 * mass[11];
    for(int i = 0; i < 3; i++)
    {
        if(maxx != wet_nw[i] && maxx2 != wet_nw[i]) return_am += wet_nw[i] * mass[9];
    }
    return return_am;
}


double triple(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    double return_am = 0;
    int maxx = -1;
    int x = -1, y = -1, z = -1;
    for(int i = 0; i < 3; i++)
        for(int j = i + 1; j < 4; j++)
            for(int k = j + 1; k < 5; k++)
                if (wet[i] == wet[j] && wet[i] == wet[k] && maxx < wet[j])
                {
                    maxx = wet[j];
                    x = i;
                    y = j;
                    z = k;
                }
    int wet_nw[2];
    int j = 0;
    for(int i = 0; i < 5; i++)
    {
        if (i != x && i != y && i != z)
        {
            wet_nw[j] = wet[i];
            j++;
        }
    }
    if (maxx == -1) return 0;
    if (wet_nw[0] > wet_nw[1]) std::swap(wet_nw[0], wet_nw[1]);
    std::sort(wet_nw, wet_nw + 3);
    return_am += maxx * mass[14];
    return_am += wet_nw[1] * mass[13];
    return_am += wet_nw[0] * mass[12];
    return return_am;
}

double strit(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    std::sort(wet, wet + 5);
    for(int i = 0; i < 4; i++)
    {
        if(wet[i + 1] - wet[i] != 1) return 0;
    }
    return wet[4] * mass[15];
}

double flesh(card* cards)
{
    double return_am = 0;
    int wet[5], suit[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
        suit[i] = cards[i].suit;
    }
    std::sort(wet, wet + 5);
    for(int i = 0; i < 4; i++)
    {
        if(suit[i + 1] != suit[i]) return 0;
    }
    for(int i = 0; i < 5; i++)
    {
        return_am += wet[i] * mass[16 + i];
    }
    return return_am;
}

double full_house(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    double return_am = 0;
    int maxx = -1;
    int x = -1, y = -1, z = -1;
    for(int i = 0; i < 3; i++)
        for(int j = i + 1; j < 4; j++)
            for(int k = j + 1; k < 5; k++)
                if (wet[i] == wet[j] && wet[i] == wet[k] && maxx < wet[j])
                {
                    maxx = wet[j];
                    x = i;
                    y = j;
                    z = k;
                }
    int wet_nw[2];
    int j = 0;
    for(int i = 0; i < 5; i++)
    {
        if (i != x && i != y && i != z)
        {
            wet_nw[j] = wet[i];
            j++;
        }
    }
    if (maxx == -1) return 0;
    if (wet_nw[0] != wet_nw[1]) return 0;
    return_am += wet_nw[0] * mass[21];
    return_am += maxx * mass[22];
    return return_am;
}

double kare(card* cards)
{
    int wet[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
    }
    double return_am = 0;
    int maxx = -1;
    for(int i = 0; i < 2; i++)
        for(int j = i + 1; j < 3; j++)
            for(int k = j + 1; k < 4; k++)
                for(int m = k + 1; m < 5; m++)
                    if (wet[i] == wet[j] && wet[i] == wet[k] && wet[i] == wet[m] && maxx < wet[j])
                    {
                        maxx = wet[j];
                    }
    int j = -1;
    for(int i = 0; i < 5; i++)
    {
        if (wet[i] != maxx)
        {
            j = wet[i];
        }
    }
    if (maxx == -1) return 0;
    return_am += j * mass[23];
    return_am += maxx * mass[24];
    return return_am;
}

double strit_flesh(card* cards)
{
    int wet[5], suit[5];
    for(int i = 0; i < 5; i++)
    {
        wet[i] = cards[i].weight;
        suit[i] = cards[i].suit;
    }
    std::sort(wet, wet + 5);
    for(int i = 0; i < 4; i++)
    {
        if(wet[i + 1] - wet[i] != 1 || suit[i + 1] != suit[i]) return 0;
    }
    return wet[4] * mass[25];
}

void game::round(bool g_flag)
{
    if (g_flag)rised = 40;
    int m;
    if (!after_card_getting) delete[] after_card_getting;
    after_card_getting = new int[player_amount];

    if (g_flag)
    {
        if (!folded) delete[] folded;
        folded = new bool[player_amount];
    }
    bool getting_card[10];
    for (int i = 0; i < player_amount ; i++ )
    {
        after_card_getting[i] = 0;
        if (g_flag) folded[i] = false;
        getting_card[i] = g_flag;
    }
    int tmp = (diller + 1) % player_amount;
    do
    {
        card * player_cards = gplayers[tmp].get_cards(cards);
        int size = gplayers[tmp].get_size(cards);
        std::string s_cards = "";
        card k;
        for ( int i = 0; i < size ; i++ )
        {
            k = player_cards[i];
            s_cards += k.get_weight();
            s_cards += k.get_suit();
            s_cards += " ";
        }

        if (g_flag) std::cout << "First Round" << std::endl;
        else std::cout << "Second Round" << std::endl;
        std::cout << "Now it's you turn to play, " << gplayers[tmp].get_name() << "." << std::endl <<
                  "Your cards are : " << s_cards << std::endl <<
                  "Your balance is : " << gplayers[tmp].get_balance() << std::endl <<
                  "Your bank in game is : " << putts[tmp] << std::endl;
        if (getting_card[tmp])
        {
            std::cout << "To drop cards write : numbers of cards," << std::endl <<
                      "for example you write 534 you'll drop 5, 3 and 4 cards" << std::endl;
            std::cin >> s_cards;
            drop_cards(true, tmp, s_cards);
            getting_card[tmp] = false;
        }
        std::string flag;
        std::string money;
        do
        {
            std::cout << "You can fold your cards (write : f)," << std::endl <<
                      "call to " << rised << " (write : c)," << std::endl <<
                      "rise upper then " << rised + 40 << " (write : r sum), where sum is amount of rising sum to," << std::endl <<
                      "remember that bank is " << rised << ", so your max rise is :" << gplayers[tmp].get_balance() - rised + putts[tmp] << std::endl;

            std::cin >> flag;
            if(flag == "r")
                std::cin >> money;
        }
        while(call_check(tmp, flag, money));
        std::cout << "Your balance is : " << gplayers[tmp].get_balance() << std::endl <<
                  "Your bank in game is : " << putts[tmp] << std::endl;
        tmp++;
        tmp %= player_amount;
        m = 0;
        while ((folded[tmp] || gplayers[tmp].get_balance() == 0) && m < 10)
        {
            tmp++;
            tmp %= player_amount;
            m++;
        }
        std::cout << "Now it's turn of " << gplayers[tmp].get_name() << "," << std::endl <<
                  "let him enter any key" << std::endl;
        std::string s;
        if (m < 10) std::cin >> s;
        system("cls");
        delete[] player_cards;
    }
    while (small_check() && m < 10);
}

bool game::call_check(int tmp, std::string flag, std::string mone)
{
    if ("f" == flag)
    {
        drop_cards(false, tmp, "all");
        folded[tmp] = true;
        return false;
    }
    if ("r" == flag)
    {
        for(unsigned int j = 0; j < mone.length(); j++)
        {
            if (!isdigit(mone[j])) return true;
        }
        int money = atoi(mone.c_str());
        if (money < 40 || money + rised - putts[tmp] > gplayers[tmp].get_balance())
            return true;
        gplayers[tmp].balance -= money + rised - putts[tmp];
        putts[tmp] += money + rised - putts[tmp];
        rised += money;
        return false;
    }
    if ("c" == flag)
    {
        if (rised == putts[tmp])
            return false;
        if(rised > gplayers[tmp].get_balance() + putts[tmp])
        {
            putts[tmp] += gplayers[tmp].get_balance();
            gplayers[tmp].balance = 0;
        }
        else
        {
            gplayers[tmp].balance -= rised - putts[tmp];
            putts[tmp] = rised;
        }
        return false;
    }
    return true;
}

void game::drop_cards(bool flag, int tmp, std::string nums)
{
    std::vector<int> cards_nums;
    std::string p_name = gplayers[tmp].get_name();
    for (int i = 0; i < 52 ; i++)
        if (p_name == cards[i].get_owner())
            cards_nums.push_back(i);
    if (nums == "all")
        for(unsigned int i = 0; i < cards_nums.size(); i++)
            cards[cards_nums[i]].owner = "";
    for (unsigned int i = 0; i < nums.length(); i++)
        if (isdigit(nums[i]))
        {
            char* ch = new char[1];
            ch[0] = nums[i];
            int itr = atoi(ch);
            delete[] ch;
            if(itr > 0 && itr < 6)
            {
                cards[cards_nums[itr - 1]].owner = "";
                if (flag)
                {
                    after_card_getting[tmp]++;
                }
            }
        }
}


void game::init_money(bool flag)
{

    int tmp = diller % player_amount;
    if (flag)
    {
        if (!putts) delete[] putts;
        putts = new int[player_amount];
        for (int i = 0; i < player_amount; i++)
            putts[i] = 0;
    }
    if (gplayers[tmp].balance < 40)
    {
        banck += gplayers[tmp].balance;
        putts[tmp] += gplayers[tmp].balance;
        gplayers[tmp].balance = 0;
    }
    else
    {
        banck += 40;
        putts[tmp] += 40;
        gplayers[tmp].balance -= 40;
    }

    tmp++;
    tmp %= player_amount;
    if (gplayers[tmp].balance < 20)
    {
        banck += gplayers[tmp].balance;
        putts[tmp] += gplayers[tmp].balance;
        gplayers[tmp].balance = 0;
    }
    else
    {
        banck += 20;
        putts[tmp] += 20;
        gplayers[tmp].balance -= 20;
    }
    diller++;
    rised += 40;
}


void game::init_players()
{
    human_player* players = new human_player[player_amount];
    for (int i = 0; i < player_amount ; i++ )
    {
        players[i] = human_player(sbalance, names[i]);
    }
    if(!gplayers) delete[] gplayers;
    gplayers = players;
}

void game::shake_cards()
{
    for (int i = 0; i < 52 ; i++ )
        cards[i] = closed_card(i);
    std::srand ( unsigned ( std::time(0) ) );
    card tmp;
    int h;
    for (int i = 0; i < 52; i++)
    {
        h = std::rand() % 52;
        tmp = cards[i];
        cards[i] = cards[h];
        cards[h] = tmp;
        //std::swap(cards[i],cards[std::rand()%52]);
    }
    glob_card_pointer = 0;
    for(int i = 0; i < player_amount * 5; i++)
    {
        cards[i] = open_card(gplayers[i / 5].get_name(), cards[i]);
        glob_card_pointer++;
    }
}

