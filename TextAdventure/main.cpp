#include <iostream>
#include "Game.h"
#include "Menu.h"

int main() {

	std::srand(static_cast<unsigned>(time(NULL)));
	//Init Game engine
	Game game;

	//Game loop
	if (game.showMenu() == true)
	{
		while (game.running() && !game.getEndGame()) {
			//Update
			game.update();

			//Render
			game.render();

		}
	}
	//End of application
	return 0;
}