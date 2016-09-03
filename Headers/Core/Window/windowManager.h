#pragma once

#include <irrlicht.h>

// Windower class
// Does not create window,(as its done via createDevice(), and thus far, I don't know a way of manually setting window size without re-creating the entire irrlicht device :()
// Instead, this class is pretty minimal, it just listens for window resize events, and updates its public "windowinfo" for other classes to get from
namespace Sping
{
	class Core;

	// Small struct just holding the window's gamma stats that getGammaRamp() can fill
	struct GammaInfo
	{
		irr::f32 red;
		irr::f32 green;
		irr::f32 blue;
		irr::f32 brightness;
		irr::f32 contrast;
	};

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
		// Gamma ramp details
		GammaInfo gammaRamp;
		// Device type. Win32, x11 etc.
		irr::E_DEVICE_TYPE deviceType;
		// Is current window fullscreen
		bool isFullscreen;
		// Is current window active
		bool isActive;
		// Is current window focused
		bool isFocused;
		// String displayed on the top of the window
		std::string titleText;
	};
	
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		int init(Sping::Core *core);

		// Checks whether resize/other event has occured
		// TODO: irr::IVideoDriver has some func's you'd probably use to check stuff
		void tick();

		// Maximizes window, duh
		void maximize();
		// Minimizes window, duh
		void minimize();
		
		inline const WindowInfo *getInfo()
		{
			return &this->_info;
		}

	protected:
		

	private:
		Sping::Core *_core;

		WindowInfo _info;

	};
}