#include <Game/game.h>
#include <iostream>

#define D 8

// Entry point, you nincompoop
int main()
{
	std::cout << "HELLO\n";

	if (8==D)
	{
		try 
		{
			Sping::Game game;
		}
		catch (std::exception err)
		{
			std::cout << "Exception encountered!\n" << err.what() << std::endl;
		}
	}
	else
	{
		std::cout << "You shall not pass :(\n";
	}

	std::cout << "FROM THE OTHER SIIIIIIIIIDE\n";

	return 0;
}