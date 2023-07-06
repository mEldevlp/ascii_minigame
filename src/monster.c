#include "rogue.h"

#define MAX_MONSTERS 6

int add_monsters(Level* level)
{
    level->monsters = (Monster**)malloc(sizeof(Monster*) * MAX_MONSTERS);
    level->number_of_monsters = 0;
    for (size_t x = 0; x < level->number_of_rooms; ++x)
    {
        //if(rand() % 2 == 0)
        if(true)
        {
            level->monsters[level->number_of_monsters] = select_monster(level->num_of_level);
            set_start_position(level->monsters[level->number_of_monsters], level->rooms[x]);
            level->number_of_monsters++;
        }
    }
}

Monster* select_monster(int num_of_level)
{
    int monster = -1;
    switch(num_of_level)
    {
        case 1: case 2: case 3:
            monster = (rand() % 2) + 1;
            break;
        case 4: case 5:
            monster = (rand() % 2) + 2;
            break;

        case 6:
            monster = 3;
    }

    switch(monster)
    {   
        case 1: return create_monster('X', 3, 1, 1, 1, 1);  // spider
        case 2: return create_monster('G', 9, 3, 1, 1, 2);  // goblin
        case 3: return create_monster('T', 20, 5, 1, 1, 1); // troll
    }
}

Monster* create_monster(char symbol, int health, int attack, int speed, int defence, int pathfinding)
{
    Monster* new_monster = (Monster*)malloc(sizeof(Monster));
    new_monster->symbol = symbol;
    new_monster->health = health;
    new_monster->attack = attack;
    new_monster->speed = speed;
    new_monster->defence = defence;
    new_monster->pathfinding = pathfinding;
    new_monster->is_alive = true;

    return new_monster;
}

int kill_monster(Monster* monster)
{
    mvaddch(monster->position->y, monster->position->x, Obj_DOT);
    monster->is_alive = false;

    return 1;
}

int set_start_position(Monster* monster, Room* room)
{
    monster->position = (Position*)malloc(sizeof(Position));

    monster->position->y = (1 + rand() % (room->height - 2)) + room->position->y;
    monster->position->x = (1 + rand() % (room->width - 2)) + room->position->x;
    attron(COLOR_PAIR(3));
    mvaddch(monster->position->y, monster->position->x, monster->symbol);
    attroff(COLOR_PAIR(3));
    refresh();
}

int move_monsters(Level* level)
{
    int x = 0;
    for (x = 0; x < level->number_of_monsters; ++x)
    {
        if(level->monsters[x]->is_alive == false) continue;

        mvaddch(level->monsters[x]->position->y, level->monsters[x]->position->x, Obj_DOT);

        if(level->monsters[x]->pathfinding == 1)
            pathfinding_random(level->monsters[x]->position);
        
        else
            pathfinding_seek(level->monsters[x]->position, level->player->position);
        
        attron(COLOR_PAIR(3));
        mvaddch(level->monsters[x]->position->y, level->monsters[x]->position->x, level->monsters[x]->symbol);
        attroff(COLOR_PAIR(3));
    }
}

int pathfinding_random(Position* position)
{
    int random = rand() % 5;

    switch(random)
    {
        case 0: // up
            if(mvinch(position->y -1, position->x) == Obj_DOT)
            {
                position->y--;
            }
            break;
        
        case 1: // down
            if(mvinch(position->y + 1, position->x) == Obj_DOT)
            {
                position->y++;
            }
            break;

        case 2: // left
            if(mvinch(position->y, position->x - 1) == Obj_DOT)
            {
                position->x--;
            }
            break;

        case 3: // right
            if(mvinch(position->y, position->x + 1) == Obj_DOT)
            {
                position->x++;
            }
            break;

        case 4: // nothing
            break;
    }
}

int pathfinding_seek(Position* start, Position* destination)
{
    //step left
    if(abs((start->x - 1) - destination->x) < abs(start->x - destination->x) && (mvinch(start->y, start->x - 1) == Obj_DOT))
    {
        start->x--;
    }
    //step right
    else if(abs((start->x + 1) - destination->x) < abs(start->x - destination->x) && (mvinch(start->y, start->x + 1) == Obj_DOT))
    {
        start->x++;
    }
    //step down
    else if(abs((start->y + 1) - destination->y) < abs(start->y - destination->y) && (mvinch(start->y + 1, start->x) == Obj_DOT))
    {
        start->y++;
    }
    //step up
    else if(abs((start->y - 1) - destination->y) < abs(start->y - destination->y) && (mvinch(start->y - 1, start->x) == Obj_DOT))
    {
        start->y--;
    }
}

Monster* get_monster_at(Position* position, Monster** monsters)
{
    for (size_t x = 0; x < 6; ++x)
    {
        if((position->y == monsters[x]->position->y) && (position->x == monsters[x]->position->x))
        {
            return monsters[x];
        }
    }

    return NULL;
    
}


/* spider
    symbol: X
    levels: 1-3
    hp : 2
    attack: 2
    speed: 1
    defence: 1
    pathfinding: 1 (random)

 goblin 
    symbol: G
    levels: 1-5
    hp : 2
    attack: 3
    speed: 1
    defence: 1
    pathfinding: 2 (seeking)

 troll
    symbol: T
    levels: 4-6
    hp : 2
    attack: 5
    speed: 1
    defence: 1
    pathfinding: 1 (random)
 l*/

