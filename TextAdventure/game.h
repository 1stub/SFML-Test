#pragma once

#include <iostream>
#include <vector>
#include <ctime>

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

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	//Private Functions
	void initVariables();
	void initWindow();
	void initEnemies();

public: 
	//Constructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void renderEnemies();
	void update();
	void render();

};

#endif
