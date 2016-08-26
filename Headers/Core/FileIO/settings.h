#pragma once

#include <irrlicht.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <tinyxml2/tinyxml2.h>

// Class which reads settings from xml file
// Constructor grabs first-time settings
namespace Sping
{
	class Core;

	enum class DataType
	{
		BOOL,
		INT,
		FLOAT,
		DOUBLE,
		STRINGW,

		ALL // if youre too lazy to set
	};

	class Data
	{
	public:
		Data();
		~Data();

		Data(
			bool boolVal,
			int intVal,
			float floatVal,
			double doubleVal,
			const irr::core::stringw &stringwVal,
			DataType type = DataType::ALL
			);

		// C++ really needs trivial getters and setters like c#
		inline bool getBool()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::BOOL) ? this->_bool : 0;
		}

		inline int getInt()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::INT) ? this->_int : 0;
		}

		inline float getFloat()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::FLOAT) ? this->_float : 0.0f;
		}

		inline double getDouble()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::DOUBLE) ? this->_double : 0.0;
		}

		inline irr::core::stringw getStringw()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::STRINGW) ? this->_stringw : "N/A";
		}

		inline DataType getType()
		{
			return this->_type;
		}

	protected:


	private:
		friend class Settings;

		DataType _type = DataType::ALL;

		// Still too much of a sissy to use unions
		bool _bool;
		int _int;
		float _float;
		double _double;
		irr::core::stringw _stringw;

	};

	// Individual cluster of settings, eg all user keybindings would be a separate instance of this, and graphics settings would be another
	// Should only be constructed within Settings manager, not from other external sources
	class Setting
	{
	public:
		Setting();
		~Setting();

	protected:


	private:
		friend class Settings;

		std::unordered_map<irr::core::stringw, Data> _settingData = std::unordered_map<irr::core::stringw, Data>();

	};

	// Setting manager
	class Settings
	{
	public:
		Settings();
		~Settings();

		int init(Core *core);

		// Getter operator, looks prettier lol, returns "default stuff" if setting doesnt exist
		Data &operator()(const irr::core::stringw &category, const irr::core::stringw &settingName);

		// Change currently loaded settings at runtime, may take effect immediately
		template<typename T>
		int edit(const irr::core::stringw &category, const irr::core::stringw &settingName, const T &value)
		{
			try
			{
				Data *tempData = &this->_settings.at(category)._settingData.at(settingName);
				if (tempData == nullptr)
				{
					throw std::exception("Could not find the setting specified!\n");
					return 2;
				}
				
				switch (tempData->getType())
				{
				case DataType::BOOL:
					tempData->_bool = value;
					break;
				case DataType::INT:
					tempData->_int = value;
					break;
				case DataType::FLOAT:
					tempData->_float = value;
					break;
				case DataType::DOUBLE:
					tempData->_double = value;
					break;
				case DataType::STRINGW:
					tempData->_stringw = value;
					break;
				default:
					throw std::exception("Invalid type specified!\n");
					break;
				}
			}
			catch (std::exception err)
			{
				return 1;
			}
		}

		// Set whether "shouldSave" to be true
		void shouldSave(bool should = true);

		int shutdown();

	protected:
		

	private:
		Core *_core;

		int loadAll();
		int load(const irr::core::stringw &category);

		// Write to file, should be called on shutdown, if anything was edited
		int saveAll();
		int save(const irr::core::stringw &category);

		// If true, it means someone's changed a setting during runtime and they've chosen that settings should be re-saved before exiting.
		// Once true, stays true till saved at shutdown
		bool _shouldSave = false;

		std::unordered_map<irr::core::stringw, Setting> _settings = std::unordered_map<irr::core::stringw, Setting>();

		irr::core::stringw _prefix = "Resources/Settings/";
		irr::core::stringw _suffix = ".xml";

		// List of all individual settings files to load onto memory
		std::vector<irr::core::stringw> _categories = std::vector<irr::core::stringw>(
		{
			"Device"
			// TODO: other settings, eg graphical, key bindings etc...
		}
			);

		// "Null reference" if you're idiotic enough to request for a nonexistant setting
		Data _dataRef = Data(
			0,
			0,
			0.0f,
			0.0,
			"Null"
			);

	};
}