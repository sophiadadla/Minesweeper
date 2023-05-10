#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "random.h"
#include <chrono>
#include <SFML/System.hpp>
#include "LeaderBoard.h"
using namespace std;

#ifndef MINESWEEPER_GAMEBOARD_H
#define MINESWEEPER_GAMEBOARD_H


class GameBoard{

struct Tile{
        vector<Tile*> AdjTiles;
        int numAdjMines = 0;
        int row;
        int col;
        sf::Vector2i tilepos;
        sf::Sprite thistilesprite;
        sf::Sprite cover;
        bool isFlag = false;
        bool isRevealed = false;
        bool isMine = false;
        bool isNum = false;
        bool showsMine = false;

        Tile(sf::Texture *tex, int xcord, int ycord){
            thistilesprite.setTexture(*tex);
            thistilesprite.setPosition(xcord, ycord);
            tilepos.x = xcord;
            tilepos.y = ycord;
            row = ycord/32;
            col = xcord/32;
        }

        void setFlag(sf::Texture *tex){
            isFlag = true;
            cover.setTexture(*tex);
            cover.setPosition(tilepos.x, tilepos.y);

        }
        void setNum(sf::Texture *tex){
            isNum = true;
            cover.setTexture(*tex);
            cover.setPosition(tilepos.x, tilepos.y);
        }

        void setMine(sf::Texture *tex){
            showsMine = true;
            cover.setTexture(*tex);
            cover.setPosition(tilepos.x, tilepos.y);
        }

        void AdjacentMines(){
            for(unsigned int f = 0; f< AdjTiles.size(); f++){
                if(AdjTiles.at(f)->isMine)
                {
                    numAdjMines+=1;
                }
            }
        }

    };



struct Button{
    sf::Sprite buttonsprite;

    Button(sf::Texture *tex){
        buttonsprite.setTexture(*tex);
    }

    };

public:
    vector<Tile> tiles;
    vector<Button> buttons;
    vector<int> mineindices;
    map<string, sf::Texture>texturemap;
    string cols;
    string rows;
    string mines;
    string minecountStr;
    string seconds;
    string minutes;
    int secs;
    int mins;
    int width;
    int height;
    int nummines;
    int minecount;
    int tilecount;
    bool gameover = false;
    bool debugOn = false;
    bool isPaused = false;
    bool leaderboardOn = false;
    bool win = false;
    sf::Time elapsed;
    sf::Time pausedtime;
    string usertimestring;
    int usertime;
    string user;

GameBoard(int initwidth, int initheight, string username);

void DisplayBoard();

void ReadConfig();

void ResetBoard();

void RecursiveReveal(Tile& tile, vector<Tile>& tiles);

};


#endif //MINESWEEPER_GAMEBOARD_H
