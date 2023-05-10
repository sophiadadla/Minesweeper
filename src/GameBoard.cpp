#include "GameBoard.h"


GameBoard::GameBoard(int initwidth, int initheight, string username) {
    sf::Texture hidden;
    texturemap.emplace("hidden", hidden);
    texturemap["hidden"].loadFromFile("files/images/tile_hidden.png");
    sf::Texture happy;
    texturemap.emplace("happy", happy);
    texturemap["happy"].loadFromFile("files/images/face_happy.png");
    sf::Texture debug;
    texturemap.emplace("debug", debug);
    texturemap["debug"].loadFromFile("files/images/debug.png");
    sf::Texture pause;
    texturemap.emplace("pause", pause);
    texturemap["pause"].loadFromFile("files/images/pause.png");
    sf::Texture leaderboard;
    texturemap.emplace("leaderboard", leaderboard);
    texturemap["leaderboard"].loadFromFile("files/images/leaderboard.png");
    sf::Texture flag;
    texturemap.emplace("flag", flag);
    texturemap["flag"].loadFromFile("files/images/flag.png");
    sf::Texture mine;
    texturemap.emplace("mine", mine);
    texturemap["mine"].loadFromFile("files/images/mine.png");
    sf::Texture revealed;
    texturemap.emplace("revealed", revealed);
    texturemap["revealed"].loadFromFile("files/images/tile_revealed.png");
    sf::Texture num1;
    texturemap.emplace("num1", num1);
    texturemap["num1"].loadFromFile("files/images/number_1.png");
    sf::Texture num2;
    texturemap.emplace("num2", num2);
    texturemap["num2"].loadFromFile("files/images/number_2.png");
    sf::Texture num3;
    texturemap.emplace("num3", num3);
    texturemap["num3"].loadFromFile("files/images/number_3.png");
    sf::Texture num4;
    texturemap.emplace("num4", num4);
    texturemap["num4"].loadFromFile("files/images/number_4.png");
    sf::Texture num5;
    texturemap.emplace("num5", num5);
    texturemap["num5"].loadFromFile("files/images/number_5.png");
    sf::Texture num6;
    texturemap.emplace("num6", num6);
    texturemap["num6"].loadFromFile("files/images/number_6.png");
    sf::Texture num7;
    texturemap.emplace("num7", num7);
    texturemap["num7"].loadFromFile("files/images/number_7.png");
    sf::Texture num8;
    texturemap.emplace("num8", num8);
    texturemap["num8"].loadFromFile("files/images/number_8.png");
    sf::Texture win;
    texturemap.emplace("win", win);
    texturemap["win"].loadFromFile("files/images/face_win.png");
    sf::Texture lose;
    texturemap.emplace("lose", lose);
    texturemap["lose"].loadFromFile("files/images/face_lose.png");
    sf::Texture digits;
    texturemap.emplace("digits", digits);
    texturemap["digits"].loadFromFile("files/images/digits.png");
    sf::Texture play;
    texturemap.emplace("play", play);
    texturemap["play"].loadFromFile("files/images/play.png");

    width = initwidth;
    height = initheight;
    user = username;
}

void GameBoard::DisplayBoard(){
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    LeaderBoard leader1(width, height);
    window.clear(sf::Color::White);

    for(unsigned int r = 0; r < stoi(rows); r++){
        for(unsigned int c = 0; c < stoi(cols); c++){
            int x = c*32;
            int y = r*32;
            Tile newtile(&texturemap["hidden"], x, y);
            tiles.push_back(newtile);
            window.draw(newtile.thistilesprite);
        }
    }

    //populate AdjTiles
    for(unsigned int i = 0; i < tiles.size(); i++){
        for(int dy = -1; dy <= 1; dy++){
            for(int dx = -1; dx <= 1; dx++){
                if(dx == 0 && dy == 0){
                    continue;
                }
                int nr = tiles[i].row + dy;
                int nc = tiles[i].col + dx;
                if(nr < 0 || nr >= stoi(rows) || nc < 0 || nc >= stoi(cols)){
                    continue;
                }
                int index = nr * stoi(cols) + nc;
                tiles[i].AdjTiles.push_back(&tiles[index]);
            }
        }
    }


    Button happybutton(&texturemap["happy"]);
    buttons.push_back(happybutton);
    Button debugbutton(&texturemap["debug"]);
    buttons.push_back(debugbutton);
    Button pausebutton(&texturemap["pause"]);
    buttons.push_back(pausebutton);
    Button leaderboardbutton(&texturemap["leaderboard"]);
    buttons.push_back(leaderboardbutton);

    minecountStr = to_string(minecount);
    if(minecountStr.substr(0, 1)=="-") {
        minecountStr = minecountStr.substr(1);
        sf::Sprite minecounter;
        minecounter.setTexture(texturemap["digits"]);
        minecounter.setTextureRect(sf::IntRect(210, 0, 21, 32));
        minecounter.setPosition(12, 32 * (stoi(rows) + 0.5f) + 16);
        window.draw(minecounter);

    }
    for (unsigned int i = 0; i < minecountStr.length(); i++) {
        sf::Sprite minecounter;
        minecounter.setTexture(texturemap["digits"]);
        int thisnum = stoi(minecountStr.substr(i, 1));
        minecounter.setTextureRect(sf::IntRect(thisnum * 21, 0, 21, 32));
        minecounter.setPosition(33 + i * 21, 32 * (stoi(rows) + 0.5f) + 16);
        window.draw(minecounter);
    }

    happybutton.buttonsprite.setPosition(((stoi(cols)/2.0)*32)-32, 32*(stoi(rows)+0.5f));
    window.draw(happybutton.buttonsprite);
    debugbutton.buttonsprite.setPosition((stoi(cols)*32)-304, 32*(stoi(rows)+0.5f));
    window.draw(debugbutton.buttonsprite);
    pausebutton.buttonsprite.setPosition((stoi(cols)*32)-240, 32*(stoi(rows)+0.5f));
    window.draw(pausebutton.buttonsprite);
    leaderboardbutton.buttonsprite.setPosition((stoi(cols)*32)-176, 32*(stoi(rows)+0.5f));
    window.draw(leaderboardbutton.buttonsprite);

    //generate randoms mines
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<std::mt19937::result_type> dist(0, tilecount-1);

    //make a list of random mine indices
    while(mineindices.size() < nummines){
        int x = dist(rng);
        if(find(mineindices.begin(), mineindices.end(), x)==mineindices.end()){
            mineindices.push_back(x);
        }
    }

    // set mine bool
    for(unsigned int i = 0; i < nummines; i++){
        tiles.at(mineindices.at(i)).isMine = true;
    }

    //calc how many AdjMines
    for(unsigned int i = 0; i< tiles.size(); i++){
        tiles.at(i).AdjacentMines();
    }

    sf::Clock clock;
    sf::Clock pauseclock;

    while (window.isOpen())
    {
        if(!gameover)
            happybutton.buttonsprite.setTexture(texturemap["happy"]);
        pausebutton.buttonsprite.setTexture(texturemap["pause"]);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (!leaderboardOn){

                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    sf::Vector2f newpos = window.mapPixelToCoords(pos); // gets mouse position

                    if (debugbutton.buttonsprite.getGlobalBounds().contains(newpos)) {
                        if (!gameover) {
                            if (!debugOn) {
                                for (unsigned int i = 0; i < tiles.size(); i++) {
                                    if (tiles.at(i).isMine && !tiles.at(i).isFlag) {
                                        tiles.at(i).setMine(&texturemap["mine"]);
                                    }
                                }
                                debugOn = true;
                            } else {
                                for (unsigned int i = 0; i < tiles.size(); i++) {
                                    if (tiles.at(i).isMine) {
                                        tiles.at(i).showsMine = false;
                                        tiles.at(i).thistilesprite.setTexture(texturemap["hidden"]);
                                    }
                                    if (tiles.at(i).isFlag) {
                                        tiles.at(i).setFlag(&texturemap["flag"]);
                                    }
                                }
                                debugOn = false;
                            }
                        }
                    }


                    if (happybutton.buttonsprite.getGlobalBounds().contains(newpos)) {// smiley button
                        ResetBoard();
                        clock.restart();
                        happybutton.buttonsprite.setTexture(texturemap["happy"]);
                        pausebutton.buttonsprite.setTexture(texturemap["pause"]);

                    }
                    if (pausebutton.buttonsprite.getGlobalBounds().contains(newpos)) {// pause button
                        if (!gameover) {
                            if (!isPaused) { //pause game
                                pausebutton.buttonsprite.setTexture(texturemap["play"]);
                                pauseclock.restart();
                                isPaused = true;
                            } else { // unpause game
                                pausedtime += pauseclock.getElapsedTime();
                                pausebutton.buttonsprite.setTexture(texturemap["pause"]);
                                isPaused = false;

                            }
                        }
                    }
                    if(leaderboardbutton.buttonsprite.getGlobalBounds().contains(newpos)){// leaderboard button
                        leaderboardOn = true;
                        pauseclock.restart();
                        for(unsigned int r = 0; r < stoi(rows); r++){
                            for(unsigned int c = 0; c < stoi(cols); c++){
                                int x = c*32;
                                int y = r*32;
                                sf::Sprite temptile;
                                temptile.setTexture(texturemap["revealed"]);
                                temptile.setPosition(x, y);
                                window.draw(temptile);
                            }
                        }
                        window.display();
                        if(!gameover || !win){
                            leader1.writeLeaderBoard();
                        }
                        else{
                            leader1.CheckWinTime(user, usertime, usertimestring);

                        }
                        leader1.DisplayLeaderBoard();
                    }


                    if (event.mouseButton.button == sf::Mouse::Right) {           //SETS FLAG
                        for (unsigned int i = 0; i < tiles.size(); i++) {
                            if (tiles.at(i).thistilesprite.getGlobalBounds().contains(newpos)) {
                                if (!gameover) {
                                    if (!tiles.at(i).isRevealed) {
                                        if (!tiles.at(i).isFlag) {
                                            tiles.at(i).setFlag(&texturemap["flag"]);
                                            minecount -= 1;
                                        } else {
                                            tiles.at(i).thistilesprite.setTexture(texturemap["hidden"]);
                                            minecount += 1;
                                            tiles.at(i).isFlag = false;
                                        }
                                    }
                                }
                            }
                        }
                    } else if (event.mouseButton.button == sf::Mouse::Left) {      //REVEAL MINE
                        for (unsigned int i = 0; i < tiles.size(); i++) {
                            if (tiles.at(i).thistilesprite.getGlobalBounds().contains(newpos)) {
                                if (!gameover) {
                                    if (!tiles.at(i).isFlag) {
                                        if (!tiles.at(i).isMine) {
                                            if (tiles.at(i).numAdjMines == 0) {
                                                tiles.at(i).thistilesprite.setTexture(texturemap["revealed"]);
                                                RecursiveReveal(tiles.at(i), tiles);
                                            } else if (tiles.at(i).numAdjMines == 1) {
                                                tiles.at(i).setNum(&texturemap["num1"]);
                                            } else if (tiles.at(i).numAdjMines == 2) {
                                                tiles.at(i).setNum(&texturemap["num2"]);
                                            } else if (tiles.at(i).numAdjMines == 3) {
                                                tiles.at(i).setNum(&texturemap["num3"]);
                                            } else if (tiles.at(i).numAdjMines == 4) {
                                                tiles.at(i).setNum(&texturemap["num4"]);
                                            } else if (tiles.at(i).numAdjMines == 5) {
                                                tiles.at(i).setNum(&texturemap["num5"]);
                                            } else if (tiles.at(i).numAdjMines == 6) {
                                                tiles.at(i).setNum(&texturemap["num6"]);
                                            } else if (tiles.at(i).numAdjMines == 7) {
                                                tiles.at(i).setNum(&texturemap["num7"]);
                                            } else if (tiles.at(i).numAdjMines == 8) {
                                                tiles.at(i).setNum(&texturemap["num8"]);
                                            }

                                            tiles.at(i).isRevealed = true;
                                        } else { // if you click a mine -> game ends
                                            for (unsigned int i = 0; i < tiles.size(); i++) {
                                                if (tiles.at(i).isMine) {
                                                    tiles.at(i).isRevealed = true;
                                                    tiles.at(i).setMine(&texturemap["mine"]);
                                                }
                                            }
                                            happybutton.buttonsprite.setTexture(texturemap["lose"]);
                                            gameover = true;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //checkwinner
        int w = nummines;
        for (unsigned int i = 0; i < tiles.size(); i++) {
            if (!tiles.at(i).isMine && tiles.at(i).isRevealed) {
                w++;
            }
        }
        if (w == tilecount) {
            gameover = true;
            win = true;
            happybutton.buttonsprite.setTexture(texturemap["win"]);
            for (unsigned int i = 0; i < tiles.size(); i++) {
                if (tiles.at(i).isMine) {
                    tiles.at(i).setFlag(&texturemap["flag"]);
                    minecount = 0;
                }
            }
            for (unsigned int i = 0; i < tiles.size(); i++) {
                window.draw(tiles.at(i).thistilesprite);
            }

            happybutton.buttonsprite.setPosition(((stoi(cols) / 2.0) * 32) - 32,32 * (stoi(rows) + 0.5f));
            window.draw(happybutton.buttonsprite);
            usertimestring = minutes+":"+seconds;
            usertime = static_cast<int>(elapsed.asSeconds());
            clock.restart();
            pauseclock.restart();
        }


        if(leaderboardOn){
            pausedtime += pauseclock.getElapsedTime();
        }

        leaderboardOn = false;

        window.clear(sf::Color::White);

            //CLOCK
            if(!isPaused && !leaderboardOn && !gameover) {
                elapsed = clock.getElapsedTime() - pausedtime;
            }
            mins = static_cast<int>(elapsed.asSeconds()) / 60;
            if (mins > 59) {
                mins = mins / 60;
            }
            secs = static_cast<int>(elapsed.asSeconds()) % 60;

            seconds = to_string(secs);
            minutes = to_string(mins);

            if (mins < 10) {
                minutes = "0" + to_string(mins);
            }
            for (unsigned int i = 0; i < minutes.length(); i++) {
                sf::Sprite clockcounter;
                clockcounter.setTexture(texturemap["digits"]);
                int thisnum = stoi(minutes.substr(i, 1));
                clockcounter.setTextureRect(sf::IntRect(thisnum * 21, 0, 21, 32));
                clockcounter.setPosition((stoi(cols) * 32) - 97 + i * 21, 32 * (stoi(rows) + 0.5f) + 16);
                window.draw(clockcounter);
            }
            if (secs < 10) {
                seconds = "0" + to_string(secs);
            }
            for (unsigned int i = 0; i < seconds.length(); i++) {
                sf::Sprite clockcounter;
                clockcounter.setTexture(texturemap["digits"]);
                int thisnum = stoi(seconds.substr(i, 1));
                clockcounter.setTextureRect(sf::IntRect(thisnum * 21, 0, 21, 32));
                clockcounter.setPosition((stoi(cols) * 32) - 54 + i * 21, 32 * (stoi(rows) + 0.5f) + 16);
                window.draw(clockcounter);
            }




        happybutton.buttonsprite.setPosition(((stoi(cols) / 2.0) * 32) - 32,32 * (stoi(rows) + 0.5f));
        window.draw(happybutton.buttonsprite);
        window.draw(debugbutton.buttonsprite);
        pausebutton.buttonsprite.setPosition((stoi(cols) * 32) - 240, 32 * (stoi(rows) + 0.5f));
        window.draw(pausebutton.buttonsprite);
        window.draw(leaderboardbutton.buttonsprite);

        for (unsigned int i = 0; i < tiles.size(); i++) {
            window.draw(tiles.at(i).thistilesprite);
        }
        for (unsigned int i = 0; i < tiles.size(); i++) {
            if(tiles.at(i).isFlag || tiles.at(i).isNum || tiles.at(i).showsMine) {
                window.draw(tiles.at(i).cover);
            }
        }

        //redraw minecount
        minecountStr = to_string(minecount);
        if (minecountStr.substr(0, 1) == "-") {
            minecountStr = minecountStr.substr(1);
            sf::Sprite minecounter;
            minecounter.setTexture(texturemap["digits"]);
            minecounter.setTextureRect(sf::IntRect(210, 0, 21, 32));
            minecounter.setPosition(12, 32 * (stoi(rows) + 0.5f) + 16);
            window.draw(minecounter);

        }
        for (unsigned int i = 0; i < minecountStr.length(); i++) {
            sf::Sprite minecounter;
            minecounter.setTexture(texturemap["digits"]);
            int thisnum = stoi(minecountStr.substr(i, 1));
            minecounter.setTextureRect(sf::IntRect(thisnum * 21, 0, 21, 32));
            minecounter.setPosition(33 + i * 21, 32 * (stoi(rows) + 0.5f) + 16);
            window.draw(minecounter);
        }

        if(isPaused){
            for(unsigned int r = 0; r < stoi(rows); r++){
                for(unsigned int c = 0; c < stoi(cols); c++){
                    int x = c*32;
                    int y = r*32;
                    sf::Sprite temptile;
                    temptile.setTexture(texturemap["revealed"]);
                    temptile.setPosition(x, y);
                    window.draw(temptile);
                }
            }
        }
        window.display();
    } // end of while loop
}

void GameBoard::ReadConfig(){
    ifstream cfile("files/board_config.cfg");
    getline(cfile, cols);
    getline(cfile, rows);
    getline(cfile, mines);
    this->width = stoi(cols)*32;
    this->height = stoi(rows)*32+100;
    this->nummines = stoi(mines);
    this->tilecount = stoi(cols)*stoi(rows);
    minecount = nummines;
}

void GameBoard::ResetBoard(){

    for(unsigned int i = 0; i< tiles.size();i++){
        tiles.at(i).isRevealed = false;
        tiles.at(i).showsMine = false;
        tiles.at(i).isNum = false;
        tiles.at(i).numAdjMines = 0;
        tiles.at(i).isFlag = false;
        tiles.at(i).isMine = false;
        tiles.at(i).thistilesprite.setTexture(texturemap["hidden"]);
    }
    secs = 0;
    mins = 0;
    pausedtime = sf::Time::Zero;
    minecount = nummines;
    gameover = false;
    debugOn = false;
    isPaused=false;
    win = false;

    //generate random mines
    static random_device rd;
    static mt19937 rng(rd());
    uniform_int_distribution<std::mt19937::result_type> dist(0, tilecount-1);

    mineindices.clear();

    //make a list of random mine indices
    while(mineindices.size() < nummines){
        int x = dist(rng);
        if(find(mineindices.begin(), mineindices.end(), x)==mineindices.end()){
            mineindices.push_back(x);
        }
    }

    // set mine bool
    for(unsigned int i = 0; i < nummines; i++){
        tiles.at(mineindices.at(i)).isMine = true;
    }

    //calc how many AdjMines
    for(unsigned int i = 0; i< tiles.size(); i++){
        tiles.at(i).AdjacentMines();
    }

    minecountStr = to_string(minecount);
    if(minecountStr.substr(0, 1)=="-") {
        minecountStr = minecountStr.substr(1);
        sf::Sprite minecounter;
        minecounter.setTexture(texturemap["digits"]);
        minecounter.setTextureRect(sf::IntRect(210, 0, 21, 32));
        minecounter.setPosition(12, 32 * (stoi(rows) + 0.5f) + 16);

    }
    for (unsigned int i = 0; i < minecountStr.length(); i++) {
        sf::Sprite minecounter;
        minecounter.setTexture(texturemap["digits"]);
        int thisnum = stoi(minecountStr.substr(i, 1));
        minecounter.setTextureRect(sf::IntRect(thisnum * 21, 0, 21, 32));
        minecounter.setPosition(33 + i * 21, 32 * (stoi(rows) + 0.5f) + 16);
    }
}

void GameBoard::RecursiveReveal(Tile& tile, vector<Tile>& tiles){
    for(unsigned int f = 0; f < tile.AdjTiles.size(); f++){
        if (!tile.AdjTiles.at(f)->isMine && !tile.AdjTiles.at(f)->isRevealed && !tile.AdjTiles.at(f)->isFlag) {
            tile.AdjTiles.at(f)->isRevealed = true;
            if(tile.AdjTiles.at(f)->numAdjMines == 0){
                tile.AdjTiles.at(f)->thistilesprite.setTexture(texturemap["revealed"]);
                RecursiveReveal(*tile.AdjTiles.at(f), tiles);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 1){
                tile.AdjTiles.at(f)->setNum(&texturemap["num1"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 2){
                tile.AdjTiles.at(f)->setNum(&texturemap["num2"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 3){
                tile.AdjTiles.at(f)->setNum(&texturemap["num3"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 4){
                tile.AdjTiles.at(f)->setNum(&texturemap["num4"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 5){
                tile.AdjTiles.at(f)->setNum(&texturemap["num5"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 6){
                tile.AdjTiles.at(f)->setNum(&texturemap["num6"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 7){
                tile.AdjTiles.at(f)->setNum(&texturemap["num7"]);
            }
            else if(tile.AdjTiles.at(f)->numAdjMines == 8){
                tile.AdjTiles.at(f)->setNum(&texturemap["num8"]);
            }

        }
    }
}