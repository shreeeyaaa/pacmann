#include "MainMenu.h"
#include"Global.h"

MainMenu::MainMenu(sf::RenderWindow& window) : m_window(window)//, m_showingRules(false)
{
    if (!m_texture.loadFromFile("mm.png")) {
        // Handle error if image loading fails
        // You can throw an exception or handle it in some other way
    }
    m_sprite.setTexture(m_texture);

    if (!m_soundBuffer.loadFromFile("pacman_eatfruit.wav")) {
        std::cout << "Error loading sound" << std::endl;
    }
    m_sound.setBuffer(m_soundBuffer);

}



void MainMenu::run() {



    handleEvents();

    update();
    render();

}


void MainMenu::handleEvents() {
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

                    // Print mouse position for testing
                    //std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;


                    // Check if the mouse position is within a specific area
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 167 && mousePosition.y < 205) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 1 play" << std::endl;
                        //pacman beginning sound try
                        m_sound.play();


                    }
                    //for option 2 how to play
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 239 && mousePosition.y < 266) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 2 how to play" << std::endl;
                        m_sound.play();
                        // m_showingRules = true;

                    }
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 308 && mousePosition.y < 338) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 3 exit" << std::endl;
                        m_sound.play();
                    }

                }
            }
        }
    }
}
int MainMenu::draw() {
   m_window.setView(sf::View(sf::FloatRect(0, 0,672,704)));

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

                    // Print mouse position for testing
                    //std::cout << "Mouse Position: (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;


                    // Check if the mouse position is within a specific area
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 167 && mousePosition.y < 205) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 1 play" << std::endl;
                        //pacman beginning sound try
                        m_sound.play();
                        return 1;


                    }
                    //for option 2 how to play
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 239 && mousePosition.y < 266) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 2 how to play" << std::endl;
                        m_sound.play();
                        return 2;


                    }
                    if (mousePosition.x > 202 && mousePosition.x < 477 && mousePosition.y > 308 && mousePosition.y < 338) {
                        // Perform a specific task for clicks in the specified area
                        std::cout << "option 3 exit" << std::endl;
                        m_sound.play();
                        return 3;

                    }

                }
            }
        }

        m_window.clear();
        // Draw your content here
        m_window.draw(m_sprite);
        m_window.display();
    }
}
void MainMenu::update() {
    /* if (m_showingRules) {
         m_rulesWindow.show();
     }*/
}

void MainMenu::render() {
    m_window.clear();
    // Draw your content here
    m_window.draw(m_sprite);
    m_window.display();
}

