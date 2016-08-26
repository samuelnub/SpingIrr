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

		// Whether the main loop should continue running
		bool run();

		int shutdown();

		std::unique_ptr<Settings> settings = std::make_unique<Settings>();
		std::unique_ptr<Window> window = std::make_unique<Window>();

	protected:


	private:
		friend class Settings;
		friend class Window;

		irr::IrrlichtDevice *_device = irr::createDevice(
			irr::video::EDT_NULL
			);

	};
}