#pragma once

#include <irrlicht.h>

// Windower class, creates window, has utility functions for managing window parameters
namespace Sping
{
	class Core;

	class Window
	{
	public:
		Window();
		~Window();

		int init(Sping::Core *core);

		// Applies what you've set
		// TODO use createDeviceEx() and specify SIrrlichtCreationParameters - more control
		int apply();

		inline const irr::SIrrlichtCreationParameters *getParams()
		{
			return &this->_params;
		}

		// External parameters. do not "get" information here, as it may be outdated. Set here instead, and apply() when ready
		// TODO: read from settings in init func (preferably make a new func to call whenever youd like)
		irr::SIrrlichtCreationParameters params = irr::SIrrlichtCreationParameters();

	protected:


	private:
		Sping::Core *_core;

		irr::SIrrlichtCreationParameters _params;

	};
}