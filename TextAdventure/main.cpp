#include <iostream>
#include "Game.h"

int main() {

	std::srand(static_cast<unsigned>(time(NULL)));
	//Init Game engine
	Game game;

	//Game loop
	while (game.running() && !game.getEndGame()) {
		//Event polling

		//Update
		game.update();

		//Render
		game.render();

	}
	//End of application
	return 0;
}