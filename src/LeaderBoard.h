#ifndef MINESWEEPER_LEADERBOARD_H
#define MINESWEEPER_LEADERBOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameBoard.h"
using namespace std;

class LeaderBoard{
public:
    LeaderBoard(int initwidth, int initheight);
    void writeLeaderBoard();
    void CheckWinTime(string un, int ut, string utt);
    void DisplayLeaderBoard();
    int width;
    sf::Font font;
    int height;
    sf::Text leaderboard;
    sf::FloatRect leaderboardtextRect = leaderboard.getLocalBounds();
    sf::FloatRect numtextrect;
    vector<string> names;
    vector<string>times;
    vector<int>timeinseconds;
    string all;
};


#endif //MINESWEEPER_LEADERBOARD_H
