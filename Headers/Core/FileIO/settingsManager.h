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
		STRING,

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
			const std::string &stringVal,
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

		inline std::string getString()
		{
			return (this->getType() == DataType::ALL || this->getType() == DataType::STRING) ? this->_string : "N/A";
		}

		inline DataType getType()
		{
			return this->_type;
		}

	protected:


	private:
		friend class SettingsManager;

		DataType _type = DataType::ALL;

		// Still too much of a sissy to use unions
		bool _bool;
		int _int;
		float _float;
		double _double;
		std::string _string;

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
		friend class SettingsManager;

		std::unordered_map<std::string, Data> _settingData = std::unordered_map<std::string, Data>();

	};

	// Setting manager
	class SettingsManager
	{
	public:
		SettingsManager();
		~SettingsManager();

		int init(Core *core);

		// Getter operator, looks prettier lol, returns "default stuff" if setting doesnt exist
		Data &operator()(const std::string &category, const std::string &settingName);

		// Change currently loaded settings at runtime, may take effect immediately
		template<typename T>
		int edit(const std::string &category, const std::string &settingName, const T &value)
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
				case DataType::STRING:
					tempData->_string = value;
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
		int load(const std::string &category);

		// Write to file, should be called on shutdown, if anything was edited
		int saveAll();
		int save(const std::string &category);

		// If true, it means someone's changed a setting during runtime and they've chosen that settings should be re-saved before exiting.
		// Once true, stays true till saved at shutdown
		bool _shouldSave = false;

		std::unordered_map<std::string, Setting> _settings = std::unordered_map<std::string, Setting>();

		std::string _prefix = "Resources/Settings/";
		std::string _suffix = ".xml";

		// List of all individual settings files to load onto memory
		std::vector<std::string> _categories = std::vector<std::string>(
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