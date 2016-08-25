#pragma once

#include <memory>
#include <Core/core.h>

// Pretty god-like, contains core and game-related stuff
namespace Sping
{
	class Game
	{
	public:
		Game();
		~Game();
		
		int init();

		void tick();

		// Publically accessible stuff
		// Valid thing to do in c++11
		std::unique_ptr<Sping::Core> core = std::make_unique<Sping::Core>();

	protected:


	private:


	};
}