#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define HEIGHT 29
#define WIDTH 50

int x, y;// for snake
int fruitx = 0, fruity = 0;// for fruit to be generated
int gameEnd;// when the game should get terminate we will assign it the value of 0
int flag; // to keep track of which key was pressed
int count;
int score;

char tailX[1000], tailY[1000];

void hidecursor();
void Makelogic();
void display();
void place();
void Ifhit();
void clear();

int main(void)
{
    hidecursor();
    l1:
    score = 0;
    gameEnd = 1;
    flag = 10;
    count = 0;
    place();
    while (gameEnd)
    {
        display();
        Ifhit();
        Makelogic();
    }

    char temp[100];
    sprintf(temp, "Score : %d\nPress Retry to play again", score);

    int check = MessageBox(0, temp, "Note", MB_RETRYCANCEL);

    if (check == IDRETRY)
    {
        system("cls");
        DestroyWindow(0);
        goto l1;
    }

    return 0;
}

void display()
{
    clear();
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
            {
                printf("*");
            }
            else if (i == x && j == y)
            {
                printf("O");
            }
            else if (i == fruitx && j == fruity)
            {
                printf("F");
            }
            else
            {
                int ch = 1;

                for (int k = 0; k < count; k++)
                {
                    if (i == tailX[k] && j == tailY[k])
                    {
                        printf("o");
                        ch = 0;
                    }
                }

                if (ch)
                printf(" ");
            }
        }
        printf("\n");
    }
}

void snake_position()
{
    x = HEIGHT / 2;
    y = WIDTH / 2;
}

void fruit_position()
{
    do
    {
        fruitx = rand() % HEIGHT;
    }
    while (fruitx == 0);

    do
    {
        fruity = rand() % WIDTH;
    }
    while (fruity == 0);
}

void place()
{
    snake_position();
    fruit_position();
}


void Ifhit()
{
    if (kbhit())
    {
        switch(getch())
        {
            case 'a':
                flag = 1;
                break;

            case 's':
                flag = 2;
                break;

            case 'w':
                flag = 3;
                break;

            case 'z':
                flag = 4;
                break;

            case 'x':
                flag = 5;
                break;
        }
    }
}

int checktail()
{
    for (int i = 0; i < count; i++)
    {
        if (x == tailX[i] && y == tailY[i])
        {
            gameEnd = 0;
            return 1;
        }
    }
    return 0;
}
void Makelogic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < count; i++)
    {
        int prev2X = tailX[i];
        int prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevY = prev2Y;
        prevX = prev2X;
    }
    switch(flag)
    {
        case 1:
            y--;
            break;
        case 2:
            y++;
            break;

        case 3:
            x--;
            break;

        case 4:
            x++;
            break;

        case 5:
            gameEnd = 0;
            break;
    }

    if (x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1 || checktail())
        gameEnd = 0;


    if (x == fruitx && y == fruity)
    {
        fruit_position();
        score += 10;
        count++;
    }
}

void clear()// custom cls function so that no flikker occurs
{
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
