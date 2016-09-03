#include <Core/FileIO/settingsManager.h>
#include <Core/core.h>
#include <iostream>

Sping::SettingsManager::SettingsManager()
{
}

Sping::SettingsManager::~SettingsManager()
{
}

int Sping::SettingsManager::init(Sping::Core *core)
{
	this->_core = core;

	return 0;
}

Sping::Data &Sping::SettingsManager::get(
	const std::string &category, 
	const std::string &settingName)
{
	try
	{
		return this->_settings.at(category)._settingData.at(settingName);
	}
	catch (std::exception err)
	{
		std::cout << "Could not retrieve setting in the category of \"" << category << "\" and/or a name of \"" << settingName << "\"!\n";
		return this->_dataRef;
	}
}

void Sping::SettingsManager::shouldSave(bool should)
{
	this->_shouldSave = should;
}

int Sping::SettingsManager::shutdown()
{
	if (this->_shouldSave)
	{
		this->saveAll();
	}
}

int Sping::SettingsManager::loadAll()
{
	for (auto &category : this->_categories)
	{
		if (this->load(category) != 0)
		{
			throw std::exception("Could not read a certain setting category/file!\n");
			return 1;
		}
	}

	return 0;
}

int Sping::SettingsManager::load(const std::string &category)
{
	std::string filePath = this->_prefix + category + this->_suffix;

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError xmlError = xmlDoc.LoadFile(filePath.c_str());
	if (xmlError != 0)
	{
		throw std::exception("Could not load settings file\n");
		return 1;
	}

	tinyxml2::XMLElement *xmlEle = xmlDoc.FirstChildElement(category);
	if (xmlEle != nullptr)
	{
		xmlEle = xmlEle->FirstChildElement("setting");
		if (xmlEle != nullptr)
		{
			while (xmlEle != nullptr)
			{
				std::string settingName = xmlEle->Attribute("name");
				std::string settingType = xmlEle->Attribute("type");

				Sping::Data *tempData = &this->_settings[category]._settingData[settingName];

				if (settingType == "bool")
				{
					xmlEle->QueryBoolAttribute("value", &tempData->_bool);
					tempData->_type = Sping::DataType::BOOL;
				}
				else if (settingType == "int")
				{
					xmlEle->QueryIntAttribute("value", &tempData->_int);
					tempData->_type = Sping::DataType::INT;
				}
				else if (settingType == "float")
				{
					xmlEle->QueryFloatAttribute("value", &tempData->_float);
					tempData->_type = Sping::DataType::FLOAT;
				}
				else if (settingType == "double")
				{
					xmlEle->QueryDoubleAttribute("value", &tempData->_double);
					tempData->_type = Sping::DataType::DOUBLE;
				}
				else if (settingType == "string")
				{
					tempData->_string = xmlEle->Attribute("value");
					tempData->_type = Sping::DataType::STRING;
				}
				else
				{
					throw std::exception("Unknown data type specified in settings!\n");
				}

				if (xmlEle == nullptr)
				{
					throw std::exception("Could not acquire one of the settings elements!\n");
					return 2;
				}

				std::cout << "Settings: " << category << ": Acquired setting name " << settingName << "\n";

				xmlEle = xmlEle->NextSiblingElement("setting");
			}
		}
	}

	return 0;
}

Sping::Data::Data()
{
}

Sping::Data::~Data()
{
}

Sping::Data::Data(bool boolVal, int intVal, float floatVal, double doubleVal, const std::string &stringVal, DataType type) :
	_bool(boolVal),
	_int(intVal),
	_float(floatVal),
	_double(doubleVal),
	_string(stringVal),
	_type(type)
{
}

Sping::Setting::Setting()
{
}

Sping::Setting::~Setting()
{
}
