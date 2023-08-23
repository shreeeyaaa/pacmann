#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include "Global.h"
#include "DrawText.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"
#include "ConvertSketch.h"
#include "DrawMap.h"
#include "MapCollision.h"
#include"MainMenu.h"
#include"Howtoplay.h"
#include<iostream>
#include"file.h"

int main()
{
	enum GameState {
		mainmenu,
		HowToPlay,
		PlayGame,
		Exit
	};

	GameState currentState = mainmenu;

	//int a=0, b=0;
	//Is the game won?
	bool game_won = 0;

	//Used to make the game framerate-independent.
	unsigned lag = 0;
	//lag along with delta time stores the time elapsed between last frame change

	unsigned char level = 0;

	//Similar to lag, used to make the game framerate-independent.
	std::chrono::time_point<std::chrono::steady_clock> previous_time;
	//creates a variable named previous_time of time_point(template class of c++ standard library chrono)
	//holds a particular time point of <std::chrono::steady_clock> clock

	//It's not exactly like the map from the original Pac-Man game, but it's close enough.
	//creates a two-dimensional array (technically an array of strings) named map_sketch to represent a map layout.
	std::array<std::string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	//Initial ghost positions.
	std::array<Position, 4> ghost_positions;

	//SFML thing. Stores events, I think.
	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(672,704), "Pac-Man", sf::Style::Close);
	//Resizing the window making sure the player sees the relevant parts of the game environment.
	//window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));
	user u1(window);
	
	MainMenu mainMenu(window);
	//Howtoplay howtoplay;
	
	while (currentState != Exit) {
		switch (currentState) {
		case mainmenu:
			
			int choice;
			choice= mainMenu.draw();
			switch (choice) {
			case 1:
				currentState = PlayGame;
				break;
			case 2:
				currentState = HowToPlay;
				break;
			case 3:
				currentState = Exit;
				break;
			}
			break;

		case Exit:
			//std::cout << "hi" << std::endl;
			window.close();
			//currentState = mainmenu;
			break;

		case HowToPlay:
			int a;
			a=u1.onlylb();
			//int b;
			//Howtoplay howtoplay;
			//b=howtoplay.show();
			//std::cout << "How to Play:\n";
			// Display instructions on how to play the game
			///*if (b == 1) {
			//	currentState = mainmenu;
			//}*/
			// Return to the main menu after reading instructions
			//break;
			currentState = mainmenu;
			/*if (a == 1) {
				mainMenu.draw();
			}*/

			break;

		case PlayGame:
			std::cout << "Playing the game...\n";
			//window.setView(sf::View(sf::FloatRect(0, 0, 672,704)));

			//window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE* MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));
			GhostManager ghost_manager;
			
			Pacman pacman;

			//Generating a random seed.
			srand(static_cast<unsigned>(time(0)));

			map = convert_sketch(map_sketch, ghost_positions, pacman);

			ghost_manager.reset(level, ghost_positions);

			//Get the current time and store it in a variable.
			previous_time = std::chrono::steady_clock::now();
			//if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			//{
			//	std::cout << "escape pressed" << std::endl;
			//	currentState = mainmenu; // Return to the main menu after playing
			//	break;
			//}
			bool escapePressed = false;

			while (1 == window.isOpen() && !escapePressed)

			{

				window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE* MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));


				//Here we're calculating the lag.
				unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

				lag += delta_time;

				previous_time += std::chrono::microseconds(delta_time);

				//While the lag exceeds the maximum allowed frame duration.
				while (FRAME_DURATION <= lag)
				{
					//We decrease the lag.
					lag -= FRAME_DURATION;

					while (1 == window.pollEvent(event))
					{
						switch (event.type)
						{
						case sf::Event::Closed:
						{
							//Making sure the player can close the window.
							window.close();
						}
						case sf::Event::KeyPressed:
							if (event.key.code == sf::Keyboard::Escape)
							{
								// Exit the while loop if the Escape key is pressed.
								std::cout << "escape pressed" << std::endl;
								currentState = mainmenu;
								//currentState = mainmenu; // Return to the main menu after playing
								escapePressed = true; // Set the flag to exit the loop
								break;
								//return 3;
								//mainMenu.draw();
								// Return to the main menu after playing
								
							}
							break;
						}
					}

					if (0 == game_won && 0 == pacman.get_dead())
					{
						game_won = 1;

						pacman.update(level, map);

						ghost_manager.update(level, map, pacman);

						//We're checking every cell in the map.
						for (const std::array<Cell, MAP_HEIGHT>& column : map)
						{
							for (const Cell& cell : column)
							{
								if (Cell::Pellet == cell) //And if at least one of them has a pellet.
								{
									game_won = 0; //The game is not yet won.

									break;
								}
							}

							if (0 == game_won)
							{
								break;
							}
						}

						if (1 == game_won)
						{
							pacman.set_animation_timer(0);
						}
					}
					else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Restarting the game.
					{
						game_won = 0;

						if (1 == pacman.get_dead())
						{
							level = 0;
						}
						else
						{
							//After each win we reduce the duration of attack waves and energizers.
							level++;
						}

						map = convert_sketch(map_sketch, ghost_positions, pacman);

						ghost_manager.reset(level, ghost_positions);

						pacman.reset();
					}
					else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						std::cout << "escape pressed" << std::endl;
						currentState = mainmenu; // Return to the main menu after playing
						break;
					}//Restarting the game.

					//I don't think anything needs to be explained here.
					if (FRAME_DURATION > lag)
					{
						window.clear();

						if (0 == game_won && 0 == pacman.get_dead())
						{
							draw_map(map, window);

							ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window);

							draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);
						}

						pacman.draw(game_won, window);


						if (1 == pacman.get_animation_over())
						{
							if (1 == game_won)
							{
								draw_text(1, 0, 0, "Next level!", window);
							}
							else
							{
								draw_text(1, 0, 0, "Game over ", window);
								u1.display();
								
							}
						}
						
						window.display();
					}
				}


			}
			//mainMenu.draw();
			//if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			//{
			//	std::cout << "escape pressed" << std::endl;
			//	currentState = mainmenu; // Return to the main menu after playing
			//	break;
			//}

			// Your game logic goes here
			currentState = mainmenu; // Return to the main menu after playing
		    break;
		}
	}
	
}
