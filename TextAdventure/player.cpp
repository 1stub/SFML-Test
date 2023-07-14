#include "player.h"
#include <string>

Player::Player()
{
	playerName;
}

std::string Player::getName()
{
	std::string playerName;
	std::cout << "Welcome Adventurer. What would you like to name your character? \n";
	std::cin >> playerName;
	std::cout << std::endl;
	return playerName;
}

int Player::getAttack()
{
	return 0;
}

int Player::getDefense()
{
	return 0;
}
