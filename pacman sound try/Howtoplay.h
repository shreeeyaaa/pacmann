
#pragma once
#include <sfml/graphics.hpp>
#include <sfml/audio.hpp>
#include <iostream>


class Howtoplay {
public:
    Howtoplay();

    int show();

private:
    // include necessary sfml components
    sf::RenderWindow h_window;
    sf::Texture h_texture;
    sf::Sprite h_sprite;
    sf::SoundBuffer h_soundBuffer;
    sf::Sound h_sound;


    // other member variables and functions
};