#include <Core/FileIO/settings.h>
#include <Core/core.h>

#include <boost/lexical_cast.hpp>

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

Sping::Data &Sping::Settings::operator()(
	const irr::core::stringw &category, 
	const irr::core::stringw &settingName)
{
	try
	{
		return this->_settings.at(category)._settingData.at(settingName);
	}
	catch (std::exception err)
	{
		return this->_dataRef;
	}
}

void Sping::Settings::shouldSave(bool should)
{
	this->_shouldSave = should;
}

int Sping::Settings::shutdown()
{
	if (this->_shouldSave)
	{
		this->saveAll();
	}
}

int Sping::Settings::load(const irr::core::stringw &category)
{

	//TODO: use tinyxml2 instead, as it can query doubles and a few more data types, and im more familiar with it

}

Sping::Data::Data()
{
}

Sping::Data::~Data()
{
}

Sping::Data::Data(bool boolVal, int intVal, float floatVal, double doubleVal, const irr::core::stringw &stringwVal, DataType type) :
	_bool(boolVal),
	_int(intVal),
	_float(floatVal),
	_double(doubleVal),
	_stringw(stringwVal),
	_type(type)
{
}

Sping::Setting::Setting()
{
}

Sping::Setting::~Setting()
{
}
