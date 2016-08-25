#include <Core/Device/device.h>
#include <Core/core.h>

Sping::Device::Device()
{
}

Sping::Device::~Device()
{
}

int Sping::Device::init(Sping::Core *core)
{
	this->_core = core;

	return 0;
}
