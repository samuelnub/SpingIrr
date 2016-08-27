#include <Core/core.h>
#include <iostream>

Sping::Core::Core()
{
}

Sping::Core::~Core()
{
}

int Sping::Core::init()
{
	this->settingsManager->init(this);
	this->windowManager->init(this);
	
	return 0;
}

bool Sping::Core::run()
{
	return this->_device->run();
}

int Sping::Core::shutdown()
{
	std::cout << "Dropping main device!\n";
	this->_device->drop();

	return 0;
}
