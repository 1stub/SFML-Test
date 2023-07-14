#pragma once

#include <iostream>
#include <string>

const int MAX_HEALTH = 20;

class Player
{
	public:
		Player();
		std::string getName();
		int getAttack();
		int getDefense();
	private:
		std::string playerName;
		int playerPoints = 15;
};
