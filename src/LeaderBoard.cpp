#include "LeaderBoard.h"
#include "GameBoard.h"
#include <sstream>

LeaderBoard::LeaderBoard(int initwidth, int initheight){
    width = initwidth/2;
    height = initheight/2;
}

void LeaderBoard::CheckWinTime(string un, int ut, string utt){
    fstream inFile("files/leaderboard.txt",ios_base::in);

    names.clear();
    times.clear();
    timeinseconds.clear();

    string line;
    while (getline(inFile, line)) {
        string name;
        string time;
        stringstream ss(line);
        getline(ss, time, ','); // time
        getline(ss, name); //name
        times.push_back(time);
        names.push_back(name);
    }

    inFile.close();


    for(unsigned int i =0; i<times.size(); i++){
        size_t pos = times.at(i).find(':');
        std::string minutesStr = times.at(i).substr(0, pos);
        std::string secondsStr = times.at(i).substr(pos + 1);
        int minutes = std::stoi(minutesStr);
        int seconds = std::stoi(secondsStr);
        int total_seconds = minutes * 60 + seconds;
        timeinseconds.push_back(total_seconds);
    }

    for(unsigned int i = 0; i <names.size(); i++) {
        size_t pos = names.at(i).find('*');
        if (pos != std::string::npos) {
            names.at(i).erase(pos, 1);
        }
    }

    if(!names.size()){
            timeinseconds.push_back(ut);
            names.push_back(un + "*");
            times.push_back(utt);
    }
    else if (names.size()<5){
        for (unsigned int i = 0; i < timeinseconds.size(); i++) {
            if(names.at(i) == un + "*" && times.at(i) == utt){
                break;
            }
            else if (names.at(i) == un && times.at(i) == utt){
                names.at(i) = un + "*";
                break;
            }
            else if (ut < timeinseconds.at(i)) { // remove *
                timeinseconds.insert(timeinseconds.begin() + i, ut);
                names.insert(names.begin() + i, un + "*");
                times.insert(times.begin() + i, utt);
                break;
            }
            else{
                names.push_back(un);
                times.push_back(utt);
                timeinseconds.push_back(ut);
            }
        }
    }
    else {
        for (unsigned int i = 0; i < timeinseconds.size(); i++) {
            if(names.at(i) == un + "*" && times.at(i) == utt){
                break;
            }
            else if (names.at(i) == un && times.at(i) == utt){
                names.at(i) = un + "*";
                break;
            }
            else if (ut < timeinseconds.at(i)) { // remove *
                timeinseconds.insert(timeinseconds.begin() + i, ut);
                names.insert(names.begin() + i, un + "*");
                times.insert(times.begin() + i, utt);
                if (names.size() > 5){
                    timeinseconds.pop_back();
                names.pop_back();
                times.pop_back();
                }
                break;
            }
        }
    }


    fstream outFile("files/leaderboard.txt",ios_base::out);
    outFile<<"";
    for(unsigned int i =0; i<times.size(); i++){
        outFile << times.at(i)<<","<<names.at(i)<<endl;
    }

    outFile.close();

    all = "\n\n";

    for(unsigned int i =0; i<times.size(); i++){
        all+= to_string(i+1)+".\t" +times.at(i)+"\t"+names.at(i)+"\n\n";
    }

}

void LeaderBoard::writeLeaderBoard(){
    fstream inFile("files/leaderboard.txt",ios_base::in);

    names.clear();
    times.clear();
    timeinseconds.clear();

    string line;
    while (getline(inFile, line)) {
        string name;
        string time;
        stringstream ss(line);
        getline(ss, time, ','); // time
        getline(ss, name); //name
        times.push_back(time);
        names.push_back(name);
    }

    inFile.close();


    fstream outFile("files/leaderboard.txt",ios_base::out);
    outFile<<"";
    for(unsigned int i =0; i<times.size(); i++){
        outFile << times.at(i)<<","<<names.at(i)<<endl;
    }

    outFile.close();

    all = "\n\n";

    for(unsigned int i =0; i<times.size(); i++){
        all+= to_string(i+1)+".\t" +times.at(i)+"\t"+names.at(i)+"\n\n";
    }
}

void LeaderBoard::DisplayLeaderBoard(){
    font.loadFromFile("files/font.ttf");
    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    leaderboard.setFont(font);
    leaderboard.setString("LEADERBOARD");
    leaderboard.setCharacterSize(20); // in pixels, not points!
    leaderboard.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboard.setPosition(width/2.0f, height/2.0f-120);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        window.clear(sf::Color::Blue);

        // inside the main loop, between window.clear() and window.display()
        window.draw(leaderboard);

        //text positioning
        leaderboardtextRect = leaderboard.getLocalBounds();
        leaderboard.setOrigin(leaderboardtextRect.width/2,leaderboardtextRect.height/2);


            sf::Text num;
            num.setFont(font);
            num.setString(all);
            num.setCharacterSize(18); // in pixels, not points!
            num.setStyle(sf::Text::Bold);
            num.setPosition(width/2.0f, height/2.0f+20);


            numtextrect = num.getLocalBounds();
            num.setOrigin(numtextrect.width/2, numtextrect.height/2 +20);

        window.draw(num);

        window.display();

    }
}