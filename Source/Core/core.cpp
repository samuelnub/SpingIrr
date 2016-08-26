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

bool Sping::Core::run()
{
	return this->_device->run();
}
