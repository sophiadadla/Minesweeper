#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#ifndef MINESWEEPER_WELCOMEWINDOW_H
#define MINESWEEPER_WELCOMEWINDOW_H

class WelcomeWindow{
public:
    WelcomeWindow(int initwidth, int initheight);
    void DisplayWelcome();
    bool boardopen = true;
    int width;
    string username;
    int height;
    sf::Font font;
    sf::Text welcome;
    sf::FloatRect welcometextRect = welcome.getLocalBounds();
    sf::Text prompt;
    sf::FloatRect prompttextRect = prompt.getLocalBounds();
    sf::Text input;
    string inputtext = "|";
    sf::FloatRect inputtextRect = input.getLocalBounds();

};


#endif //MINESWEEPER_WELCOMEWINDOW_H
