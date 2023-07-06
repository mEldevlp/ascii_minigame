#include "rogue.h"

#define VERSION "0.0.5.0"

int main(void)
{
    Level* level;
    Position* new_position;
    int action = 0;
    screen_setup();

    int focus_index = 0;
    bool start_game = false;

    Position cursor;
    cursor.x = 50;
    cursor.y = 12;

    mvprintw(cursor.y, cursor.x + 2, "Start game");
    mvprintw(cursor.y + 2, cursor.x + 2,"Settings");
    mvprintw(cursor.y + 4, cursor.x + 2,"Exit");

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);  // text , textbg;
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);
    

    attron(COLOR_PAIR(6));
    mvaddch(cursor.y, cursor.x, '>');
    attroff(COLOR_PAIR(6));
    // Main menu loop
    while(!start_game)
    {
        action = getch();
        switch (action)
        {
            case 'w':
            {
                if(focus_index != 0)
                {
                    attron(COLOR_PAIR(4));
                    mvaddch(cursor.y, cursor.x, ' ');
                    cursor.y -= 2;
                    attron(COLOR_PAIR(6));
                    mvaddch(cursor.y, cursor.x, '>');
                    focus_index--;
                }
                break;
            }
            case 's':
            {
                if(focus_index != 2)
                {
                    attron(COLOR_PAIR(4));
                    mvaddch(cursor.y, cursor.x, ' ');
                    cursor.y += 2;
                    attron(COLOR_PAIR(6));
                    mvaddch(cursor.y, cursor.x, '>');
                    focus_index++;
                }
                break;
            }
            case ' ':
            {
                if(focus_index == 0)
                {
                    start_game = true;
                    clear();
                    init_game();
                    refresh();
                    break;
                }
                else if(focus_index == 1)
                {
                    clear();
                    refresh();
                    break;
                }
                else if(focus_index == 2)
                {
                    endwin();
                    return 0;
                }
            }
        }
    }

    attroff(COLOR_PAIR(4));
    attroff(COLOR_PAIR(6));

    level = create_level(1);
    update_info(level->player);
    mvprintw(1,0, "\tLast action <%c>", ' ');
    move(level->player->position->y, level->player->position->x);
    // Game loop
    while ((action = getch()) != 'q')
    {
        mvprintw(1,0, "\tLast action <%c>", action);
        new_position = handle_input(action, level->player);
        check_position(new_position, level);
        move_monsters(level);
        update_info(level->player);
        move(level->player->position->y, level->player->position->x);
        refresh();
    }

    // end_game();
    
    endwin();
    return 0;
}

int update_info(Player* p)
{
    move(28, 0);
    printw("\tHP: %3d | frags: %3d | golds: %3d" , p->health, p->frags, 0);
    move(29, 0);
    printw("\tPosition: [%2d, %2d]", p->position->x, p->position->y);
}

bool screen_setup()
{
    SEED = abs(time(NULL) + time(NULL));
    srand(SEED);  // random seed
    initscr();

    noecho();
    refresh();

    return true;
}

int init_game()
{
    attron(COLOR_PAIR(1));
    move(29, 100);
    printw("by mEldevlp");

    attroff(COLOR_PAIR(1));
    move(0, 0);
    printw("\tVersion %s-alpha\tSEED: %d" , VERSION, SEED);
}