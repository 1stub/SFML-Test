#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#ifndef GAME_H
#define GAME_H

//Class that acts as the game engine.

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse pos
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Game logic
	std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
	float startingMovement = 2.f;
	bool endGame;
	int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Private Functions
	void initVariables();
	void initFonts();
	void initWindow();
	void initText();
	void initEnemies();

public: 
	bool showMenu();
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void updateText();
	void update();
	void render();

};

#endif
