#include <termios.h>
#include<stdio.h>

#ifndef KBHIT_H
#define KBHIT_H

enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};

class Snake{
    private:
        bool gameOver;
        int width, height;
        int headX, headY, fruitX, fruitY;
        int tailX[100], tailY[100];
        int score, ntail;
        eDirection dir;
    public:
        Snake(int ,int);
        void generatefruit();
        bool isOver();
        void Input();
        void Draw();
        void Logic();
};  
    
class keyboard{
    public:
        keyboard();
        ~keyboard();
        int kbhit();
        char getch();

    private:
        struct termios initial_settings, new_settings;
        int peek_character;
};
    
#endif


/*
* 
*/