#include "Game.h"

//Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new 	sf::RenderWindow (this->videoMode, "Adventure", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}

//Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}

// Accessors

void Game::spawnEnemy()
{
	//Spawns enemies and sets their color + position.
	// - Adds enemies to the vector
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
		);
	this->enemy.setFillColor(sf::Color::Green);
	//Spawn Enemies
	this->enemies.push_back(this->enemy);
	//Remove Enemies at end of screen
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	//Updating the timer for enemy spawining
	if (this->enemies.size() < this->enemySpawnTimerMax)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}
	//Moving and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);

		//Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				//Gain Points
				this->points += 10.f;
			}
		}
		//if the enemy is off the screen delete enemy
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		//Final Delete of enemy
		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}

}

void Game::renderEnemies()
{
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

//Functions
void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();

}

void Game::render()
{
	/*
		@return void
		- clear old frame
		- render objects
		- display frame in window
		Renders the game objects
	*/

	this->window->clear();

	//Draw game objects
	this->renderEnemies();
	this->window->display();
}

