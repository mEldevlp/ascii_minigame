#include "rogue.h"

Player* player_init()
{
    Player* player = (Player*)malloc(sizeof(Player));
    player->position = (Position*)malloc(sizeof(Position));

    player->position->x = 14;
    player->position->y = 14;
    player->frags = 0;
    player->attack = 2;
    player->health = 100;

    // Spawn point
    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);

    return player;
}

Position* handle_input(int input, Player* player)
{
    Position* new_position = (Position*)malloc(sizeof(Position));
    new_position->y = 0;
    new_position->x = 0;

    switch (input)
    {
    case 'w': case 'W':
        new_position->y = player->position->y - 1;
        new_position->x = player->position->x;
        break;
        
    case 's': case 'S':
        new_position->y = player->position->y + 1;
        new_position->x = player->position->x;
        break;
        
    case 'a': case 'A':
        new_position->y = player->position->y;
        new_position->x = player->position->x - 1;
        break;
        
    case 'd': case 'D':
        new_position->y = player->position->y;
        new_position->x = player->position->x + 1;
        break;

        default: break;
    }

    return new_position;
    //check_position(new_position, p_player);
}

int check_position(Position* position, Level* level)
{
    switch (mvinch(position->y, position->x))
    {
        case Obj_DOT:
            player_move(position, level->player, level->tiles); break;
        //case '$':
        //case '!':
        case  COLOR_PAIR(3) | 'X': case COLOR_PAIR(3) |'G': case COLOR_PAIR(3) |'T':
            combat(level->player, get_monster_at(position, level->monsters), 1);

        default:    move(level->player->position->y, level->player->position->x); 
    }
}

int player_move(Position* position, Player* player, unsigned** tiles)
{
    mvaddch(player->position->y, player->position->x, tiles[player->position->y][player->position->x]);
    player->position->y = position->y;
    player->position->x = position->x;

    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x); // cursor on player
    
    refresh();
}


