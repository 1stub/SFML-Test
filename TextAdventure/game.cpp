#include "Game.h"
#include "Menu.h"

//Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->health = 10;
}

void Game::initFonts()
{
	if(!this->font.loadFromFile("Roboto-Regular.ttf"));
		std::cout << "FONT FAILED TO LOAD" << std::endl;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new 	sf::RenderWindow (this->videoMode, "Adventure", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f,10.f);
}

bool Game::showMenu()
{
	Menu menu(window->getSize().x, window->getSize().y);
	bool playPressed = false;  // Flag to track if "Play" button is pressed
	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play button has been pressed" << std::endl;
						playPressed = true;
						break;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						window->close();
						break;
					}

					break;
				}
				break;

			case sf::Event::Closed:
				window->close();

				break;

			}
		}
		window->clear();

		menu.drawMenu(*window);

		window->display();

		if (playPressed)
		{
			return true;
		}
	}
}

//Constructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
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

const bool Game::getEndGame() const
{
	return this->endGame;
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
	int x = rand() % 3;
	if (x == 1)
	{
		this->enemy.setSize(sf::Vector2f(25.f, 25.f));
		this->enemy.setFillColor(sf::Color::Red);
	}
	else if (x == 2)
	{
		this->enemy.setSize(sf::Vector2f(75.f, 75.f));
		this->enemy.setFillColor(sf::Color::Blue);
	}
	else
	{
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Green);
	}
	//Spawn Enemies
	if (this->enemies.size() <= maxEnemies)
	{
		this->enemies.push_back(this->enemy);
	}
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
		this->enemies[i].move(0.f, 5.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					this->points += 1.f;
					std::cout << "Points: " << this->points << std::endl;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";
	this->uiText.setString(ss.str());
}

//Functions
void Game::update()
{
	this->pollEvents();

	if (!this->endGame)
	{
		this->updateMousePositions();

		this->updateText();

		this->updateEnemies();
	}
	if (this->health <= 0)
	{
		this->endGame = true;
	}

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
	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	this->window->display();
}

