//
// Created by sophi on 4/4/2023.
//
#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(int initwidth, int initheight) {
    width = initwidth;
    height = initheight;
}

void WelcomeWindow::DisplayWelcome(){
    font.loadFromFile("files/font.ttf");
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    welcome.setFont(font); // font is a sf::Font
    welcome.setString("WELCOME TO MINESWEEPER!");
    welcome.setCharacterSize(24); // in pixels, not points!
    welcome.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcome.setOrigin(welcometextRect.width/2,welcometextRect.height/2);
    welcome.setPosition(sf::Vector2f(width/2.0f,height/2.0f-150));
    prompt.setFont(font); // font is a sf::Font
    prompt.setString("Enter your name:");
    prompt.setCharacterSize(20); // in pixels, not points!
    prompt.setStyle(sf::Text::Bold);
    prompt.setOrigin(prompttextRect.width/2,prompttextRect.height/2);
    prompt.setPosition(sf::Vector2f(width/2.0f,height/2.0f-75));input.setFont(font); // font is a sf::Font
    input.setString(inputtext);
    input.setCharacterSize(18); // in pixels, not points!
    input.setStyle(sf::Text::Bold);
    input.setFillColor(sf::Color::Yellow);
    input.setOrigin(inputtextRect.width/2,inputtextRect.height/2);
    input.setPosition(sf::Vector2f(width/2.0f,height/2.0f-45));
    window.setKeyRepeatEnabled(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    if(inputtext!="|"){
                        window.close();
                        if(inputtext.length() == 10){
                            username = inputtext;
                        }
                        else{
                            username = inputtext.substr(0, inputtext.length()-1);
                        }
                        cout <<username<<endl;
                        boardopen = false;

                    }
                }
            }


            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Backspace)
                {

                    if (inputtext!="|"){
                        inputtext.pop_back();
                        inputtext.pop_back();
                        inputtext += "|";}
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (isalpha(static_cast<char>(event.text.unicode))){
                        inputtext.pop_back();
                        inputtext += static_cast<char>(event.text.unicode);
                        if (inputtext.size() < 10) {
                            inputtext += "|";
                        }

                        if (inputtext.size() > 1) {
                            inputtext[0] = (char) toupper(inputtext[0]);
                        }
                        for (unsigned int i = 1; i < inputtext.size(); i++) {
                            inputtext[i] = (char) tolower(inputtext[i]);
                        }

                    }
                }
            }

        }
        window.clear(sf::Color::Blue);

        // inside the main loop, between window.clear() and window.display()
        window.draw(welcome);
        window.draw(prompt);

        //text positioning
        welcometextRect = welcome.getLocalBounds();
        welcome.setOrigin(welcometextRect.width/2,welcometextRect.height/2);

        prompttextRect = prompt.getLocalBounds();
        prompt.setOrigin(prompttextRect.width/2,prompttextRect.height/2);

        input.setString(inputtext);
        inputtextRect = input.getLocalBounds();
        input.setOrigin(inputtextRect.width/2,inputtextRect.height/2);
        window.draw(input);
        window.display();

    }
}