#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

class user {


public:
	user(sf::RenderWindow& window);
	void loadLeaderboard();
	void saveLeaderboard();
	int display();
	int onlylb();

	sf::RenderWindow& i_window;
	sf::Texture i_texture;
	sf::Sprite i_sprite;
};