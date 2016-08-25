#pragma once

#include <memory>
#include <irrlicht.h>
#include <Core/FileIO/settings.h>
#include <Core/Window/window.h>

// Core class, Game class should contain and initialize one of these
// This contains publically accessible members to various core stuff, duh
// The core and its members should not have any knowledge about Game
namespace Sping
{
	class Core
	{
	public:
		Core();
		~Core();

		int init();

		// Try not to use this from Game stuff
		inline irr::IrrlichtDevice *getDevice()
		{
			return this->_device;
		}

		bool shouldRun();

		std::unique_ptr<Sping::Settings> settings = std::make_unique<Sping::Settings>();
		std::unique_ptr<Sping::Window> window = std::make_unique<Sping::Window>();

	protected:


	private:
		friend class Sping::Settings;
		friend class Sping::Window;

		irr::IrrlichtDevice *_device = nullptr;

	};
}