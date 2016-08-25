#include <Core/FileIO/settings.h>
#include <Core/core.h>

Sping::Settings::Settings()
{
}

Sping::Settings::~Settings()
{
}

int Sping::Settings::init(Sping::Core *core)
{
	this->_core = core;

	return 0;
}