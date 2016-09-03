#include <Core/Input/eventManager.h>
#include <Core/core.h>
#include <iostream>
#include <climits>
#include <math.h>

Sping::EventManager::EventManager()
{
}

Sping::EventManager::~EventManager()
{
}

int Sping::EventManager::init(Core *core)
{
	std::cout << "Initializing the EventManager\n";

	this->_core = core;

	this->setupStates();
	this->setupJoysticks();

	return 0;
}

bool Sping::EventManager::OnEvent(const irr::SEvent & event)
{
	// TODO: expand this to account for more input types
	switch (event.EventType)
	{
	case irr::EET_KEY_INPUT_EVENT:
		this->processKey(event);
		break;
	case irr::EET_MOUSE_INPUT_EVENT:
		this->processMouse(event);
		break;
	case irr::EET_JOYSTICK_INPUT_EVENT:
		this->processJoystick(event);
		break;
	case irr::EET_GUI_EVENT:
		this->processGUI(event);
		break;
	default:
		break;
	}
	
	return false;
}

void Sping::EventManager::tick()
{
	for (auto &key : this->_keyStates)
	{
		switch (key.second)
		{
		case KeyState::DOWN:
			key.second = KeyState::HELD;
			break;
		case KeyState::UP:
			key.second = KeyState::RELEASED;
			break;
		default:
			break;
		}
	}

	for (auto &button : this->_mouseButtonStates)
	{
		switch (button.second)
		{
		case KeyState::DOWN:
			button.second = KeyState::HELD;
			break;
		case KeyState::UP:
			button.second = KeyState::RELEASED;
			break;
		default:
			break;
		}
	}

	this->_mouseScrolled = 0.0f;
}

bool Sping::EventManager::onKeyDown(irr::EKEY_CODE keycode)
{
	return this->_keyStates[keycode] == KeyState::DOWN;
}

bool Sping::EventManager::onKeyUp(irr::EKEY_CODE keycode)
{
	return this->_keyStates[keycode] == KeyState::UP;
}

bool Sping::EventManager::onKeyHeld(irr::EKEY_CODE keycode)
{
	return this->_keyStates[keycode] == KeyState::DOWN || this->_keyStates[keycode] == KeyState::HELD;
}

bool Sping::EventManager::onKeyReleased(irr::EKEY_CODE keycode)
{
	return this->_keyStates[keycode] == KeyState::UP || this->_keyStates[keycode] == KeyState::RELEASED;
}

bool Sping::EventManager::onMouseDown(MouseButton button)
{
	return this->_mouseButtonStates[button] == KeyState::DOWN;
}

bool Sping::EventManager::onMouseUp(MouseButton button)
{
	return this->_mouseButtonStates[button] == KeyState::UP;
}

bool Sping::EventManager::onMouseHeld(MouseButton button)
{
	return this->_mouseButtonStates[button] == KeyState::DOWN || this->_mouseButtonStates[button] == KeyState::HELD;
}

bool Sping::EventManager::onMouseReleased(MouseButton button)
{
	return this->_mouseButtonStates[button] == KeyState::UP || this->_mouseButtonStates[button] == KeyState::RELEASED;
}

bool Sping::EventManager::onMouseScrolled()
{
	return this->_mouseScrolled != 0.0f;
}

bool Sping::EventManager::onJoystickAxisMoved(irr::s32 axis, irr::u8 joystick)
{
	return this->_joysticks.size() > 0 && this->_joystickEvent.Axis[axis] != 0 && this->_joystickEvent.Joystick == joystick;
}

bool Sping::EventManager::onJoystickButtonDown(irr::u32 button, irr::u8 joystick)
{
	return this->_joysticks.size() > 0 && this->_joystickEvent.IsButtonPressed(button) && this->_joystickEvent.Joystick == joystick;
}

irr::core::dimension2d<irr::s32> Sping::EventManager::mousePos()
{
	return this->_mousePos;
}

irr::f32 Sping::EventManager::mouseScrolled()
{
	return this->_mouseScrolled;
}

irr::f32 Sping::EventManager::joystickAxisPos(irr::s32 axis, irr::f32 deadzone, irr::u8 joystick)
{
	if (this->_joysticks.size() == 0 || this->_joystickEvent.Joystick != joystick)
	{
		return 0.0f;
	}

	irr::f32 result = static_cast<irr::f32>(this->_joystickEvent.Axis[axis]) / SHRT_MAX;

	return (std::fabs(result) >= deadzone) ? result : 0.0f;
}

bool Sping::EventManager::onGUI(irr::s32 id, irr::gui::EGUI_EVENT_TYPE type)
{
	// The heck
	/*
	 Returns true if:
	 ID of gui event matches your request
	 and
	 since the default argument for the event type "doesnt exist" (its the enum count), check if it equals that, and if it does, just make it a "return true if an event happened with the ID at all/in general",
	 or else, if the event type is user-specified and it also matches the event, return true too.
	 if all else fails, it's false.
	*/
	return
		this->_guiEvent.Caller->getID() == id &&
		((this->_guiEvent.EventType == type) ? true :
		(type == irr::gui::EGET_COUNT) ? true : false);
}

int Sping::EventManager::setupStates()
{
	for (int i = 0; i < irr::EKEY_CODE::KEY_KEY_CODES_COUNT; i++)
	{
		this->_keyStates[i] = KeyState::UP;
	}
	
	for (int i = 0; i < static_cast<int>(MouseButton::ENUM_COUNT); i++)
	{
		this->_mouseButtonStates[static_cast<MouseButton>(i)] = KeyState::UP;
	}

	return 0;
}

int Sping::EventManager::setupJoysticks()
{
	if (this->_core->_device->activateJoysticks(this->_joysticks))
	{
		std::cout << this->_joysticks.size() << " joystick(s) found!\n";

		return 0;
	}

	std::cout << "No joysticks found!\n";
	return 1;
}

void Sping::EventManager::processKey(const irr::SEvent & event)
{
	if (event.KeyInput.PressedDown == true)
	{
		if (this->_keyStates[event.KeyInput.Key] != KeyState::HELD)
		{
			this->_keyStates[event.KeyInput.Key] = KeyState::DOWN;
		}
		else
		{
			this->_keyStates[event.KeyInput.Key] = KeyState::HELD;
		}
	}
	else
	{
		if (this->_keyStates[event.KeyInput.Key] != KeyState::RELEASED)
		{
			this->_keyStates[event.KeyInput.Key] = KeyState::UP;
		}
	}
}

void Sping::EventManager::processMouse(const irr::SEvent & event)
{
	if (event.MouseInput.Event == irr::EMIE_MOUSE_MOVED)
	{
		this->_mousePos.Width = event.MouseInput.X;
		this->_mousePos.Height = event.MouseInput.Y;
	}
	if (event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL)
	{
		this->_mouseScrolled = event.MouseInput.Wheel;
	}

	if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
	{
		if (this->_mouseButtonStates[MouseButton::LEFT] == KeyState::RELEASED || this->_mouseButtonStates[MouseButton::LEFT] == KeyState::UP)
		{
			this->_mouseButtonStates[MouseButton::LEFT] = KeyState::DOWN;
		}
		else
		{
			this->_mouseButtonStates[MouseButton::LEFT] = KeyState::HELD;
		}
	}
	if (event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
	{
		if (this->_mouseButtonStates[MouseButton::LEFT] != KeyState::RELEASED)
		{
			this->_mouseButtonStates[MouseButton::LEFT] = KeyState::UP;
		}
	}

	if (event.MouseInput.Event == irr::EMIE_MMOUSE_PRESSED_DOWN)
	{
		if (this->_mouseButtonStates[MouseButton::MIDDLE] == KeyState::RELEASED || this->_mouseButtonStates[MouseButton::MIDDLE] == KeyState::UP)
		{
			this->_mouseButtonStates[MouseButton::MIDDLE] = KeyState::DOWN;
		}
		else
		{
			this->_mouseButtonStates[MouseButton::MIDDLE] = KeyState::HELD;
		}
	}
	if (event.MouseInput.Event == irr::EMIE_MMOUSE_LEFT_UP)
	{
		if (this->_mouseButtonStates[MouseButton::MIDDLE] != KeyState::RELEASED)
		{
			this->_mouseButtonStates[MouseButton::MIDDLE] = KeyState::UP;
		}
	}

	if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
	{
		if (this->_mouseButtonStates[MouseButton::RIGHT] == KeyState::RELEASED || this->_mouseButtonStates[MouseButton::RIGHT] == KeyState::UP)
		{
			this->_mouseButtonStates[MouseButton::RIGHT] = KeyState::DOWN;
		}
		else
		{
			this->_mouseButtonStates[MouseButton::RIGHT] = KeyState::HELD;
		}
	}
	if (event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
	{
		if (this->_mouseButtonStates[MouseButton::RIGHT] != KeyState::RELEASED)
		{
			this->_mouseButtonStates[MouseButton::RIGHT] = KeyState::UP;
		}
	}
}

void Sping::EventManager::processJoystick(const irr::SEvent & event)
{
	std::cout << "Joystick event happened regarding joystick number " << event.JoystickEvent.Joystick << "\n";
	this->_joystickEvent = event.JoystickEvent;
}

void Sping::EventManager::processGUI(const irr::SEvent & event)
{
	std::cout << "GUI event occurred regarding the GUI element with an ID of " << event.GUIEvent.Caller->getID << "\n";
	this->_guiEvent = event.GUIEvent;
}
