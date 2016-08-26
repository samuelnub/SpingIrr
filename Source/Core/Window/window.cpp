#include <Core/Window/window.h>
#include <Core/core.h>

Sping::Window::Window()
{
}

Sping::Window::~Window()
{
}

int Sping::Window::init(Sping::Core *core)
{
	this->_core = core;

	this->apply();

	return 0;
}

int Sping::Window::apply()
{
	this->_params = this->params;

	this->_core->_device = irr::createDeviceEx(this->_params);

	if (this->_core->_device != nullptr)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
