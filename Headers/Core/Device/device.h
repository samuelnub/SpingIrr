#pragma once

// Windower class, creates window, has utility functions for 
namespace Sping
{
	class Core;

	class Window
	{
	public:
		Window();
		~Window();

		int init(Sping::Core *core);

		void set(irr::SIrrlichtCreationParameters params);

		// Applies what you've set
		// TODO use createDeviceEx() and specify SIrrlichtCreationParameters - more control
		int apply();

	protected:


	private:
		Sping::Core *_core;

		irr::SIrrlichtCreationParameters _params;

	};
}