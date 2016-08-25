#pragma once

// Windower class, creates window
namespace Sping
{
	class Core;

	class Window
	{
	public:
		Window();
		~Window();

		int init(Sping::Core *core);

	protected:


	private:
		Sping::Core *_core;

	};
}