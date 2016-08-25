#include <Game/game.h>

Sping::Game::Game()
{
	this->init();
}

Sping::Game::~Game()
{
}

int Sping::Game::init()
{
	this->core->init();

	// I know this- much is-
	while (true)
	{
		this->tick();
	}

	return 0;
}

void Sping::Game::tick()
{
}
