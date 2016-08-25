#pragma once

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

	protected:


	private:
		friend class Sping::Settings;
		friend class Sping::Window;

		irr::IrrlichtDevice *_device = nullptr;

	};
}