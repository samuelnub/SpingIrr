#pragma once

#include <memory>
#include <irrlicht.h>
#include <Core/FileIO/settingsManager.h>
#include <Core/Window/windowManager.h>
#include <Core/Input/eventManager.h>

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

		std::unique_ptr<SettingsManager> settingsManager = std::make_unique<SettingsManager>();
		std::unique_ptr<WindowManager> windowManager = std::make_unique<WindowManager>();

	protected:


	private:
		friend class SettingsManager;
		friend class WindowManager;
		friend class EventManager;

		irr::IrrlichtDevice *_device = irr::createDevice(
			irr::video::EDT_NULL
			);

	};
}