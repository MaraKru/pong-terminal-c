#include <ncurses.h>
#include <stdio.h>

#define LRX 2  // left racket
#define RRX 77 // right racket
#define LY 0   // down border
#define HY 24  // up border
#define LX 0   // left border
#define RX 79  // right border

void draw(int bx, int by, int ly, int ry, int lscore, int rscore)
{
    char up = '|';
    char down = '*';
    clear();
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            if (((x == LX) || (x == RX)))
                printw("%c", up);
            else if ((y == LY) || (y == HY))
                printw("%c", down);
            else if ((x == 38) && (lscore >= 10) && (y == 1))
                printw("%d", lscore / 10);
            else if ((x == 39) && (y == 1))
                if (lscore >= 10)
                    printw("%d", lscore % 10);
                else
                    printw("%d", lscore);
            else if ((x == 41) && (y == 1))
                if (rscore >= 10)
                    printw("%d", rscore / 10);
                else
                    printw("%d", rscore);
            else if ((x == 42) && (y == 1) && (rscore >= 10))
                printw("%d", rscore % 10);
            else if (((y == ry + 1) || (y == ry - 1) || (y == ry)) && (x == RRX)) // right racket
                printw("%c", down);
            else if (((y == ly + 1) || (y == ly - 1) || (y == ly)) && (x == LRX)) // left racket
                printw("%c", down);
            else if (x == 40)
                printw("%c", up);
            else if ((y == by) && (x == bx))
                printw("O");
            else
                printw(" ");
        }
        printw("\n");
    }
    refresh();
}

int myceil(float num, int flag)
{
    if (num - (int)num == 0.5)
    {
        if (flag)
            return ((int)num + 1);
        else
            return (int)num;
    }
    else
        return (int)num;
}

void do_score(int collision, float ball_x, int *lscore, int *rscore)
{
    if ((collision == 0) && (ball_x == LX))
    { // left player - goal!
        *lscore += 1;
    }
    else if ((collision == 0) && (ball_x == RX))
    { // right player - goal!
        *rscore += 1;
    }
    if ((*rscore > 20) && (ball_x == RX))
    {
        printw("right player win!");
    }
    else if (*lscore > 20)
    {
        printw("left player win!");
    }
}

int collision(float ball_x, float ball_y, int lr, int rr, int *lscore, int *rscore, int *restart)
{
    if ((ball_x == LRX) && ((ball_y == lr) || (ball_y == (lr + 1)) || (ball_y == (lr - 1))))
        return 1;
    else if ((ball_x == RRX) && ((ball_y == rr) || (ball_y == (rr + 1)) || (ball_y == (rr - 1))))
        return 2;
    else if ((ball_y == LY) || (ball_y == HY))
        return 3;
    else if ((ball_x == LX) || (ball_x == RX))
    {
        do_score(0, ball_x, lscore, rscore);
        *restart = 1;
        return 0;
    }
    return 0;
}

int step(float *ball_x, float *ball_y, float *ball_dx, float *ball_dy, int lr, int rr, int *lscore,
         int *rscore, int *restart)
{
    int col = collision(*ball_x, *ball_y, lr, rr, lscore, rscore, restart);
    int flag = 0;
    if (!(col))
        flag = 1; // continue a game
    else if (col == 3)
        *ball_dy = -(*ball_dy);
    else if (col == 1)
    {
        *ball_dx = -(*ball_dx);
        if (*ball_y == (lr - 1))
            *ball_dy = -1;
        else if (*ball_y == (lr + 1))
            *ball_dy = 1;
        else
            *ball_dy = 0;
    }
    else if (col == 2)
    {
        *ball_dx = -(*ball_dx);
        if (*ball_y == (rr - 1))
            *ball_dy = -1;
        else if (*ball_y == (rr + 1))
            *ball_dy = 1;
        else
            *ball_dy = 0;
    }
    *ball_x += *ball_dx;
    *ball_y += *ball_dy;
    return flag;
}

void polling(float ball_x, float ball_y, float ball_dx, float ball_dy, int ly, int ry, int lscore,
             int rscore)
{
    int whos = 0;
    int restart = 0;
    char s;
    for (;;)
    {
        s = getch();
        if ((s == 'z') && (ly < 22))
            ly += 1;
        else if ((s == 'a') && (ly > 2))
            ly -= 1;
        if ((s == 'm') && (ry < 22))
            ry += 1;
        else if ((s == 'k') && (ry > 2))
            ry -= 1;
        step(&ball_x, &ball_y, &ball_dx, &ball_dy, ly, ry, &lscore, &rscore, &restart);
        draw(myceil(ball_x, 1), myceil(ball_y, 0), ly, ry, lscore, rscore);
        if (restart)
        {
            if (whos)
                whos = 0;
            else
                whos = 1;
            restart = 0;
            ball_x = 40;
            ball_y = 12;
            ball_dy = 0;
            if ((lscore + rscore) % 2)
                ball_dx = 1;
            else
                ball_dx = -1;
        }
    }
}

int main()
{
    float ball_x = 40, ball_y = 12;
    float ball_dx = 1, ball_dy = 0;
    int ly = 12, ry = 12;
    int lscore = 0;
    int rscore = 0;
    initscr();
    noecho();
    halfdelay(1);
    polling(ball_x, ball_y, ball_dx, ball_dy, ly, ry, lscore, rscore);
    return 0;
}