
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include"file.h"
#include"MainMenu.h"
#include<iomanip>
#include<iostream>

std::vector<std::string> leaderboardNames;

user::user(sf::RenderWindow& window) : i_window(window) {
    if (!i_texture.loadFromFile("input.png")) {
        // Handle error if image loading fails
        // You can throw an exception or handle it in some other way
    }
    i_sprite.setTexture(i_texture);
}
//MainMenu mainmenu(window);
// Load names from a file
void user::loadLeaderboard() {
    std::ifstream inputFile("leaderboard.txt");
    std::string name;
    while (std::getline(inputFile, name)) {
        leaderboardNames.push_back(name);
    }
    inputFile.close();
}

// Save names to a file
void user::saveLeaderboard() {
    std::ofstream outputFile("leaderboard.txt");
    for (const std::string& name : leaderboardNames) {
        outputFile << name << "\n";
    }
    outputFile.close();
}

bool leaderboardDisplayed = false;



int user::onlylb() {
    if (leaderboardNames.empty()) {
        loadLeaderboard(); // Load data from file into leaderboardData
    }

    //loadLeaderboard(); // Load names from file

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("arcadefont.ttf")) {
        // Handle font loading error
        return 0; // Return an error code or handle it appropriately
    }

    sf::Text leaderboardText;
    leaderboardText.setFont(font);
    leaderboardText.setCharacterSize(24);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setPosition(10, 10);
    sf::Texture l_texture;
    sf::Sprite l_sprite;

    if (!l_texture.loadFromFile("lf.png")) {
        // Handle error if image loading fails
        // You can throw an exception or handle it in some other way
    }
    l_sprite.setTexture(l_texture);

    while (i_window.isOpen()) {
        sf::Event event;
        while (i_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                i_window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return 1;
            }
        }

        i_window.clear();
        i_window.draw(l_sprite);

        // Display leaderboard names
        for (size_t i = 0; i < leaderboardNames.size(); ++i) {
            leaderboardText.setString(leaderboardNames[i]);
            leaderboardText.setFillColor(sf::Color::Cyan);
            leaderboardText.setPosition(145, 231 + i * 30);

            i_window.draw(leaderboardText);
        }

        i_window.display();

    }

    return 0;
}
int user::display() {

    i_window.setView(sf::View(sf::FloatRect(0, 0, 672, 704)));


    //sf::RenderWindow inputWindow(sf::VideoMode(672, 704), "Name Input");
    //sf::Font font;
    //sf::Texture texture;
    //sf::Sprite sprite;
    //font.loadFromFile("arcadefont.ttf");
    //if (!texture.loadFromFile("input.png")) {
    //    // Handle error if image loading fails
    //    // You can throw an exception or handle it in some other way
    //}
    //sprite.setTexture(texture);
    sf::Font font;
    font.loadFromFile("arcadefont.ttf");

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(25);
    inputText.setPosition(174, 266);
    inputText.setFillColor(sf::Color::Yellow);
    std::string playerName;

    if (leaderboardNames.empty()) {
        loadLeaderboard(); // Load data from file into leaderboardData
    } // Load names from file

    while (i_window.isOpen()) {
        sf::Event event;
        while (i_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                i_window.close();
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !playerName.empty()) {
                        playerName.pop_back();
                    }
                    else if (event.text.unicode != '\r') {
                        playerName += static_cast<char>(event.text.unicode);
                    }
                    inputText.setString(playerName);
                }
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !playerName.empty()) {
                // Add the name to the leaderboard
                leaderboardNames.push_back("4   " + /*std::setw(9) << */playerName + "   546");
                //playerName.clear();
                //saveLeaderboard(); // Save names to file
                //i_window.close();
                sf::Text leaderboardText;
                leaderboardText.setFont(font);
                leaderboardText.setCharacterSize(24);
                leaderboardText.setFillColor(sf::Color::White);
                leaderboardText.setPosition(10, 10);
                sf::Texture l_texture;
                sf::Sprite l_sprite;

                if (!l_texture.loadFromFile("lf.png")) {
                    // Handle error if image loading fails
                    // You can throw an exception or handle it in some other way
                }
                l_sprite.setTexture(l_texture);

                while (i_window.isOpen()) {
                    sf::Event event;
                    while (i_window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            i_window.close();
                        }
                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                            return 1;
                            //i_window.close();
                            //mainmenu.draw();
                        }
                    }

                    i_window.clear();
                    i_window.draw(l_sprite);

                    // Display leaderboard names
                    for (size_t i = 0; i < leaderboardNames.size(); ++i) {
                        leaderboardText.setString(leaderboardNames[i]);
                        leaderboardText.setFillColor(sf::Color::Cyan);
                        leaderboardText.setPosition(145, 231 + i * 30);
                        //leaderboardText.setString(playerName);


                        i_window.draw(leaderboardText);
                    }
                    //for (size_t i = 0; i < leaderboardNames.size(); ++i) {
                    //    leaderboardText.setString(leaderboardNames[i]);

                    //    // Set different colors for odd and even indices
                    //    if (i % 2 == 0) {
                    //        leaderboardText.setFillColor(sf::Color::Cyan);
                    //    }
                    //    else {
                    //        leaderboardText.setFillColor(sf::Color::Magenta);
                    //    }

                    //    leaderboardText.setPosition(10, 10 + i * 30);
                    //    leaderboardWindow.draw(leaderboardText);
                    //}
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        //int a;
                        i_window.close();
                        //a = mainmenu.draw();
                    }
                    i_window.display();

                }

            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                //int a;
                i_window.close();
                //a = mainmenu.draw();
            }
            else if (event.type == sf::Event::Closed) {
                i_window.close();
            }
        }

        //i_window.clear();
        i_window.draw(i_sprite);
        i_window.draw(inputText);
        i_window.display();
    }

    


}
