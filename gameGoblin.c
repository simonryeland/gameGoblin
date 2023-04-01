// gcc -no-pie -Wall -o "%e" "%f" -lncurses

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define LINES 100
#define COLS 200

#define CHAR_WALL '#'
#define CHAR_SPACE ' '
#define CHAR_MAN '@'

#define KEY_ESCAPE 27

typedef struct Coord_in_win
{
    int y;
    int x;
} Coord;

Coord coord;

int map [LINES][COLS];
int ch = 0;
int lines, cols;

void init (void);
void finish(void);
void mainMap (int, int, char);
void movement (int, int, int);
// void fireMan ();

int main (void)
{
    coord.y = 11, coord.x = 41;

    init ();

    do
    {
        mainMap (lines, cols, CHAR_WALL);
        movement (ch, coord.y, coord.x);
    } while ((ch = getch ()) != KEY_ESCAPE);

    finish ();
}

void init (void)
{
    initscr ();
    savetty ();
    nonl ();
    cbreak ();
    noecho ();
    timeout (0);
    keypad (stdscr, TRUE);
    leaveok (stdscr, TRUE);
    curs_set (0);
    getmaxyx (stdscr, lines, cols);
}

void finish(void)
{
    curs_set (1);
    clear ();
    refresh ();
    resetty ();
    endwin ();
    exit (0);
}

void mainMap (int lines, int cols, char c)
{
    for (int y = 0; y <= lines; y++)
    {
        for (int x = 0; x <= cols; x++)
        {
            map[y][x] = CHAR_WALL;
            mvaddch (y, x, CHAR_WALL);
        }
    }
    for (int y = 3; y <= lines / 2; y++)
    {
        for (int x = 20; x <= cols - 20; x++)
        {
            map[y][x] = CHAR_SPACE;
            mvaddch (y, x, CHAR_SPACE);
        }
    }
}

void movement (int ch, int y, int x)
{
    mvaddch (y, x, CHAR_SPACE);
    if      (ch == KEY_UP    && map[y - 1][x] == CHAR_SPACE) y--;
    else if (ch == KEY_DOWN  && map[y + 1][x] == CHAR_SPACE) y++;
    else if (ch == KEY_LEFT  && map[y][x - 1] == CHAR_SPACE) x--;
    else if (ch == KEY_RIGHT && map[y][x + 1] == CHAR_SPACE) x++;
    mvaddch (y, x, CHAR_MAN);
    coord.y = y;
    coord.x = x;
}
