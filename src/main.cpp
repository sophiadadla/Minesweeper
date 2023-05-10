#include <SFML/Graphics.hpp>
#include <iostream>
#include "WelcomeWindow.h"
#include "GameBoard.h"
#include "LeaderBoard.h"

using namespace std;
int main()
{
    string cols;
    string rows;

    ifstream configfile("files/board_config.cfg");
    getline(configfile, cols);
    getline(configfile, rows);
    int width = stoi(cols)*32;
    int height = stoi(rows)*32+100;

    WelcomeWindow window1(width, height);
    window1.DisplayWelcome();

    GameBoard board1(width, height, window1.username);
    if(!window1.boardopen){
    board1.ReadConfig();
    board1.DisplayBoard();
    }



    return 0;
}