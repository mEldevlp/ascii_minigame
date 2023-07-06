#include "rogue.h"

Level* create_level(int num_of_level)
{
    Level* new_level = (Level*)malloc(sizeof(Level));

    new_level->num_of_level = num_of_level;
    new_level->number_of_rooms = 3; //hardcode
    new_level->rooms = room_setup();
    new_level->tiles = save_level_position();
    new_level->player = player_init();

    add_monsters(new_level);

    return new_level;
}

Room** room_setup()
{
    Room** rooms = (Room**)malloc(sizeof(Room*) * 3);

    rooms[0] = create_room(13, 13, 8, 16);
    rooms[1] = create_room(50, 2, 6, 24);
    rooms[2] = create_room(70, 11, 8, 14);

    draw_room(rooms[0]);
    draw_room(rooms[1]);
    draw_room(rooms[2]);

    connect_doors(rooms[0]->doors[3], rooms[2]->doors[1]);
    connect_doors(rooms[1]->doors[2], rooms[0]->doors[0]);

    return rooms;
}

__fastcall unsigned** save_level_position()
{
    unsigned** characters = (unsigned**)calloc(sizeof(unsigned*), 25);

    for (size_t y = 0; y < 25; y++)
    {
        characters[y] = (unsigned*)calloc(sizeof(unsigned), 100);
        for (size_t x = 0; x < 100; x++)
        {
            characters[y][x] = mvinch(y, x);
        }
    }

    return characters;
}
