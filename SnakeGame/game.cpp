#include <bits/stdc++.h>
#include <unistd.h>
#include "game.h"
using namespace std;

Snake::Snake(int w, int h) : gameOver(false), width(w), height(h)
{
    dir = STOP;
    headX = width / 2, headY = height / 2;
    generatefruit();
    score = 0;
    ntail = 0;
}

bool Snake::isOver()
{
    return gameOver;
}

void Snake::generatefruit()
{
    fruitX = rand() % (width - 1) + 1;
    fruitY = rand() % (height - 1) + 1;
}

void Snake::Input()
{
    keyboard keyb;
    if (keyb.kbhit())
    {
        switch (keyb.getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        default:
            gameOver = true;
            break;
        }
    }
}

void Snake::Draw()
{
    system("clear");
    // top Wall
    for (int i = 1; i <= width; i++)
        cout << '#';
    cout << endl;

    // left and right wall
    for (int j = 1; j < height; j++)
    {
        for (int i = 1; i <= width; i++)
        {
            if (i == 1 || i == width)
                cout << "#";
            else
            {
                if (i == headX && j == headY)
                    cout << 'O';
                else if (i == fruitX && j == fruitY)
                    cout << 'F';
                else
                {
                    bool flag = true;
                    for (int k = 0; k < ntail; k++)
                    {
                        if (i == tailX[k] && j == tailY[k])
                        {
                            cout << 'o';
                            flag = false;
                        }
                    }
                    if (flag)
                        cout << ' ';
                }
            }
        }
        cout << endl;
    }

    // bottom Wall
    for (int i = 1; i <= width; i++)
        cout << '#';
    cout << endl;
    cout << "Score :" << score << endl;
}

void Snake::Logic()
{

    // int prevX=tailX[0], prevY=tailY[0];
    for (int i = 1; i < ntail; i++)
    {
        swap(tailX[i], tailX[0]);
        swap(tailY[i], tailY[0]);
    }
    tailX[0] = headX, tailY[0] = headY;

    switch (dir)
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }

    // check for wall and fruit
    if (headX == width)
    {
        headX = 1;
    }
    else if (headX == 0)
    {
        headX = width - 1;
    }
    if (headY == height)
    {
        headY = 1;
    }
    else if (headY == 0)
    {
        headY = height - 1;
    }
    if (headX == fruitX && headY == fruitY)
    {
        score += 10;
        ntail++;
        while (headX == fruitX && headY == fruitY)
            generatefruit();
    }
    for (int k = 0; k < ntail; k++)
    {
        if (headX == tailX[k] && headY == tailY[k])
            gameOver = true;
    }
}

keyboard::keyboard()
{
    tcgetattr(0, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    peek_character = -1;
}

keyboard::~keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int keyboard::kbhit()
{
    unsigned char ch;
    int nread;
    if (peek_character != -1)
        return 1;
    new_settings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    if (nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}
char keyboard::getch()
{
    char ch;

    if (peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
    }
    else
        read(0, &ch, 1);
    return ch;
}