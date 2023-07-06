#include "rogue.h"

int combat(Player* player, Monster* monster, int order)
{
    // player attack
    if(order == 1)
    {
        monster->health -= player->attack;
        if(monster->health > 0)
        {
            player->health -= monster->attack;
        }
        else
        {
            player->frags++;
            kill_monster(monster);
        }
    }
    else // monster attack
    {
        player->health -= monster->attack;
        if(player->health > 0)
        {
            monster->health -= player->attack;
        }
    }

    return 1;
}