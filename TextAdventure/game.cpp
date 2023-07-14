#include <iostream>
#include "game.h"
#include "player.h"

int gameLoop() {
	while (int x =1) {
		std::cout << "Adventure Game" << '\n' << std::endl;
		std::cout << "1. Start \n";
		std::cout << "2. Exit\n";
		int choice{};
		std::cin >> choice;
		if (choice == 1) {
			x = 2;
			Player player;
			player.getName();
			std::cout << "Welcome, " << player.playerName << ". You have 15 points to add to the following attributes. \n What will you choose? "
		}
		else if (choice == 2) {
			return 0;
		}
		else {
			std::cout << "Please choose a valid option.\n";
		}
	}
	return 0;
}