#pragma once

#include <irrlicht.h>

// Windower class, creates window, has utility functions for managing window parameters
namespace Sping
{
	class Core;

	// Collection of specific stuff relating to display 
	// TODO: window handling
	struct WindowInfo
	{
		// Your monitor's size that the window's on
		irr::core::dimension2d<irr::u32> screenSize;
		// Window/renderer dimensions
		irr::core::dimension2d<irr::u32> windowSize;
		// Pixel depth of current monitor/display
		irr::s32 screenBitDepth;
		// Pixel depth of current video mode
		irr::s32 windowBitDepth;
		// Driver type its currently using
		irr::video::E_DRIVER_TYPE driverType;
		// Name of program, on the window bar thingy
		std::string windowName;
	};
	
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		int init(Sping::Core *core);

		// Applies what you've set
		// TODO use createDeviceEx() and specify SIrrlichtCreationParameters - more control
		int read();
		int apply();
		int readAndApply(); // Do both read from settings, and then apply

		inline const WindowInfo *getInfo()
		{
			return &this->_info;
		}

		// External parameters. do not "get" information here, as it may be outdated. Set here instead, and apply() when ready
		// TODO: read from settings in init func (preferably make a new func to call whenever youd like)
		WindowInfo parameters;

	protected:
		

	private:
		Sping::Core *_core;

		WindowInfo _info;

	};
}