#ifndef ROGUE
#define ROGUE

#include <ncursesw/curses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

static long SEED;

typedef enum Obj_Type {
    Obj_DOT = 4194430
} Obj_Type;

typedef struct Position {
    int x;
    int y;

} Position;

typedef struct Monster {
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    bool is_alive;
    Position* position;

} Monster;

typedef struct Level {
    unsigned** tiles;
    int num_of_level;
    int number_of_rooms;
    struct Player* player;
    struct Room** rooms;
    struct Monster** monsters;
    int number_of_monsters;
} Level;

typedef struct Room
{
    Position* position;
    int height;
    int width;
    Position doors[4];

    //Monster** monsters;
    //Item** items;

} Room;

typedef struct Player
{
    Position* position;
    unsigned short health;
    int attack;
    int defence;
    unsigned frags;
    //Room* room;
} Player;

// other funcs
int init_game();
bool screen_setup();
int update_info(Player*);

// level funcs
Room** room_setup();
__fastcall unsigned** save_level_position();
Level* create_level(int);

//player funcs
Player* player_init();
Position* handle_input(int, Player*);
int check_position(Position*, Level*);
int player_move(Position*, Player*, unsigned**);


// room funcs
Room* create_room(int, int, int, int);
int draw_room(Room*);
int connect_doors(Position, Position);

// Monsters funcs
int add_monsters(Level*);
Monster* select_monster(int);
Monster* create_monster(char, int, int, int, int, int);
int set_start_position(Monster*, Room*);
int move_monsters(Level*);
int pathfinding_seek(Position*, Position*);
int pathfinding_random(Position*);
Monster* get_monster_at(Position* position, Monster** monsters);
int kill_monster(Monster* monster);

//combat 
int combat(Player*, Monster*, int);

#endif