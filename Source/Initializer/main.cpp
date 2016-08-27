#include <Game/game.h>
#include <iostream>

#define IM_RICK_HARRISON 1
#define THIS_IS_MY_PAWN_SHOP 1

// Entry point, you nincompoop
int main()
{
	std::cout << "HELLO\n";

	if (IM_RICK_HARRISON && THIS_IS_MY_PAWN_SHOP)
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

	std::cout << "FROM THE OTHER SIIIIIIIIIDE\n";

	return 0;
}