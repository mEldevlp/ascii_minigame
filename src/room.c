#include "rogue.h"

Room* create_room(int x, int y, int height, int width)
{
    Room* new_room = (Room*)malloc(sizeof(Room));
    new_room->position = (Position*)malloc(sizeof(Position));
    
    new_room->position->x = x;
    new_room->position->y = y;

    new_room->height = height;
    new_room->width = width;

    // top door
    new_room->doors[0].x = rand() % (width - 2) + new_room->position->x + 1;
    new_room->doors[0].y = new_room->position->y;

    //left 
    new_room->doors[1].y = rand() % (height - 2) + new_room->position->y + 1;
    new_room->doors[1].x = new_room->position->x;

    // bottom door
    new_room->doors[2].x = rand() % (width - 2) + new_room->position->x + 1;
    new_room->doors[2].y = new_room->position->y + new_room->height - 1;

    //right 
    new_room->doors[3].y = rand() % (height - 2) + new_room->position->y + 1;
    new_room->doors[3].x = new_room->position->x + width - 1;

    return new_room;
}


int draw_room(Room* room)
{
    Position pos;

    // Create corners

    attron(COLOR_PAIR(2));
    mvaddch(room->position->y, room->position->x, ACS_ULCORNER);
    mvaddch(room->position->y, room->position->x + room->width - 1, ACS_URCORNER);
    mvaddch(room->position->y + room->height - 1, room->position->x, ACS_LLCORNER);
    mvaddch(room->position->y + room->height - 1, room->position->x + room->width - 1, ACS_LRCORNER);
    
    for (pos.x = room->position->x + 1; pos.x < room->position->x + room->width - 1; ++pos.x)
    {
        mvaddch(room->position->y, pos.x, ACS_HLINE);
        mvaddch(room->position->y + room->height - 1, pos.x, ACS_HLINE);
    }

    for (pos.y = room->position->y + 1; pos.y < room->position->y + room->height - 1; ++pos.y)
    {
        for (pos.x = room->position->x; pos.x < room->position->x + room->width; ++pos.x)
        {
            move(pos.y, pos.x); 

            if((pos.x == room->position->x) || (pos.x == room->position->x + room->width - 1))
            {
                attron(COLOR_PAIR(2));
                addch(ACS_VLINE);
            }
            else
            {
                attroff(COLOR_PAIR(2));
                addch(ACS_BULLET);
            }
        }
    }

    for (size_t i = 0; i < sizeof(room->doors) / sizeof(*room->doors); i++)
    {
        attroff(COLOR_PAIR(2));
        mvaddch(room->doors[i].y, room->doors[i].x, ACS_BULLET);
    }

    attroff(COLOR_PAIR(2));
    return 1;
}

int connect_doors(Position door_one, Position door_two)
{
    Position temp;
    Position prev;
    unsigned count = 0;

    temp.x = door_one.x;
    temp.y = door_one.y;

    prev = temp;
 
    while(true)
    {
        //step left
        if(abs((temp.x - 1) - door_two.x) < abs(temp.x - door_two.x) && (mvinch(temp.y, temp.x - 1) == ' '))
        {
            prev.x = temp.x--;
        }
        //step right
        else if(abs((temp.x + 1) - door_two.x) < abs(temp.x - door_two.x) && (mvinch(temp.y, temp.x + 1) == ' '))
        {
            prev.x = temp.x++;
        }
        //step down
        else if(abs((temp.y + 1) - door_two.y) < abs(temp.y - door_two.y) && (mvinch(temp.y + 1, temp.x) == ' '))
        {
            prev.y = temp.y++;
        }
        //step up
        else if(abs((temp.y - 1) - door_two.y) < abs(temp.y - door_two.y) && (mvinch(temp.y - 1, temp.x) == ' '))
        {
            prev.y = temp.y--;
        }
        else
        {
            if(count == 0)
            {
                temp = prev;
                count++;
                continue;
            }
            else
            {
                return 0;
            }
        }

        mvaddch(temp.y, temp.x, ACS_BULLET);
    }

    return 1;
}