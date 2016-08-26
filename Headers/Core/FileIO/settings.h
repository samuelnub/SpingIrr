#pragma once

#include <unordered_map>
#include <string>

// Class which reads settings from xml file
// Constructor grabs first-time settings
namespace Sping
{
	class Core;

	class Data
	{
	public:
		Data();
		~Data();

		// C++ really needs trivial getters and setters like c#
		inline bool getBool()
		{
			return this->_bool;
		}

		inline int getInt()
		{
			return this->_int;
		}

		inline float getFloat()
		{
			return this->_float;
		}

		inline double getDouble()
		{
			return this->_double;
		}

		inline std::string getString()
		{
			return this->_string;
		}

	protected:


	private:
		friend class Setting;

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

		inline const Data *get(const std::string name)
		{
			try
			{
				return &this->_settingData.at(name);
			}
			catch (std::exception err)
			{
				return nullptr;
			}
		}

	protected:


	private:
		friend class Settings;

		std::unordered_map<std::string, Data> _settingData;

	};

	// Setting manager
	class Settings
	{
	public:
		Settings();
		~Settings();

		int init(Core *core);

	protected:
		

	private:
		Core *_core;

	};
}