#include <Core/core.h>

Sping::Core::Core()
{
}

Sping::Core::~Core()
{
}

int Sping::Core::init()
{
	this->settings->init(this);
	this->window->init(this);

	return 0;
}

bool Sping::Core::shouldRun()
{
	// TODO: more user-configurable option (like stopping rendering loop when window isnt active)
	return this->_device->run();
}
