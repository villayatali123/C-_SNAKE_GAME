#include <bits/stdc++.h>
#include <unistd.h>
#include "game.cpp"
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    int w, h;
    cin >> w >> h;
    Snake S(w, h);
    while (!S.isOver())
    {
        S.Draw();
        S.Input();
        S.Logic();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    return 0;
}