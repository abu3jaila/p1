#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int paddle_x = 300, paddle_y = 450;
int ball_x =((rand()%570) + 50);
int ball_y = 150;
int dx = 2, dy = 2;
int score = 0;
int bricks[5][10];
char buf[10];




void initialize() {
    int i, j;

    for (i = 1; i < 5; i++) {
        for (j = 1; j < 9; j++) {
            bricks[i][j] = 1;
        }
    }
}

void draw() {
    int i, j;

    cleardevice();
    setcolor(WHITE);
    rectangle(50, 20, 570, 470);
    setfillstyle(SOLID_FILL, WHITE);
    bar(paddle_x, paddle_y, paddle_x + 100, paddle_y + 10);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(ball_x, ball_y, 10, 10);

    for (i = 1; i < 5; i++) {
        for (j = 1; j < 9; j++) {
            if (bricks[i][j] == 1) {
                setfillstyle(SOLID_FILL, BLUE);
                bar(j * 60 + 12, i * 20 + 12, j * 60 + 57, i * 20 + 27);
            }
        }
    }

    outtextxy(5, 0, "Score:");
    char str[25];
    sprintf(str, "%d", score);
    outtextxy(85, 0, str);
     outtextxy(115, 0, "|32");

}

void input() {
    if (kbhit()) {
        switch (getch()) {
        case LEFT:
            paddle_x -= 20;
            break;
        case RIGHT:
            paddle_x += 20;
            break;
        case UP:
            paddle_y -= 10;
            break;
        case DOWN:
            paddle_y += 10;
            break;
        }
    }

    if (paddle_x <= 50) {
        paddle_x = 50;
    }
    if (paddle_x >= 480) {
        paddle_x = 480;
    }
    if (paddle_y <= 420) {
        paddle_y = 420;
    }
    if (paddle_y >= 470) {
        paddle_y = 470;
    }
}

void move() {
    int i, j;

    ball_x += dx;
    ball_y += dy;

    if (ball_x >= paddle_x && ball_x <= paddle_x + 100 && ball_y >= paddle_y - 10 && ball_y <= paddle_y + 10) {
        dy = -dy;
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            if (bricks[i][j] == 1) {
                if (ball_x >= j * 60 + 10 && ball_x <= j * 60 + 60 && ball_y >= i * 20 + 10 && ball_y <= i * 20 + 30) {
                    //Beep(750, 300);
                    bricks[i][j] = 0;
                    dy = -dy;
                    score++;
                }
            }
        }
    }

    if (ball_x <= 50 || ball_x >= 570) {
        dx = -dx;
    }

    if (ball_y <= 20) {
        dy = -dy;
    }

    if (ball_y >= 470) {
        outtextxy(200, 200, "Game Over");
        outtextxy(200, 230, "Press any key to exit");
        getch();
        exit(0);
    }
    if (score == 32) {
        draw();
        outtextxy(200, 200, "Congratulations! You won the game.");
        getch();
        exit(0);
    }
}

int main() {
     int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
     readimagefile("pic.jpg", 0, 0, getmaxx(), getmaxy());

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
     outtextxy(200, 80, "Breakout GAME");
     settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
     outtextxy(50, 175, "START GAME");
    outtextxy(50, 405, "Exit GAME");
    outtextxy(180, 200, "info game :");
    settextstyle(DEFAULT_FONT, HORIZ_DIR,2);
    outtextxy(50, 220, "The game is controlled by using the right");
    outtextxy(50, 240, "and left arrows to move the paddle right");
    outtextxy(50, 260, "and left.");
   outtextxy(50, 280, "The goal is to use the paddle to direct the");
   outtextxy(50, 300, "ball towards the bricks and destroy them.");
   outtextxy(50, 320, "The more bricks you destroy,");
   outtextxy(50, 340,"the higher your score will be.");
    setcolor(BLACK);
    //rectangle(50, 150, 150, 200);
    //rectangle(50, 380, 150, 430);


    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex();
            int y = mousey();

            if (x >= 50 && x <= 150 && y >= 150 && y <= 200) {

            cleardevice();
            srand(time(NULL));
            initialize();
            draw();
      while (1) {
        move();
       input();
       draw();
       delay(10);
    }
       break;
            } else if (x >= 50 && x <= 150 && y >= 380 && y <= 430) {
                exit(0);
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }
    }

    getch();
    closegraph();



    return 0;
}
