#include <Core/Window/windowManager.h>
#include <Core/core.h>

Sping::WindowManager::WindowManager()
{
}

Sping::WindowManager::~WindowManager()
{
}

int Sping::WindowManager::init(Sping::Core *core)
{
	this->_core = core;

	this->apply();
	this->_core->_device->get
	return 0;
}

int Sping::WindowManager::read()
{
	return 0;
}

int Sping::WindowManager::apply()
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
