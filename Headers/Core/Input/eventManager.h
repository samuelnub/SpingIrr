#pragma once

#include <irrlicht.h>
#include <unordered_map>

// Event manager, borrowing aspects from http://www.irrlicht3d.org/wiki/index.php?n=Main.MastEventReceiver
namespace Sping
{
	class Core;

	enum class KeyState
	{
		// A one-time occurrence that becomes "held" in the next frame if not set to up
		DOWN,
		// A one-time occurance that becomes "released" in the next frame if not set to down
		UP,
		// A continual state which will not change unless acted upon
		HELD,
		// A continual state which will not change unless acted upon
		RELEASED
	};

	// Ignore Irrlicht's enum for mouse buttons, pfft, 1, 2, .. four??? y'alright, irrlicht?
	enum class MouseButton
	{
		LEFT,
		MIDDLE,
		RIGHT,
		ENUM_COUNT
	};

	class EventManager : public irr::IEventReceiver
	{
	public:
		EventManager();
		~EventManager();

		// Initialize this _after_ creating device
		int init(Core *core);
		
		virtual bool OnEvent(const irr::SEvent &event);

		// Resets stuff that should be reset every frame, should be done before _most_ other things ticking in the loop
		void tick();
		
		bool onKeyDown(irr::EKEY_CODE keycode);
		bool onKeyUp(irr::EKEY_CODE keycode);
		bool onKeyHeld(irr::EKEY_CODE keycode);
		bool onKeyReleased(irr::EKEY_CODE keycode);
		
		bool onMouseDown(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool onMouseUp(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool onMouseHeld(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool onMouseReleased(irr::E_MOUSE_BUTTON_STATE_MASK button);

		bool onMouseMoved();
		bool onMouseScrolled();

		// Should return false if no joysticks supported
		bool onJoystickAxisMoved(irr::s32 axis, irr::u8 joystick = 0);
		bool onJoystickButtonDown(irr::u32 button, irr::u8 joystick = 0);

		// Get mouse position. Thank irrlicht for using W and H instead of X and Y
		irr::core::dimension2d<irr::s32> mousePos();
		irr::f32 mouseScrolled();

		// Converts its raw output of a 16 bit signed short, to a float between -1 and +1, with optional deadzone, if the joystick number you request doesnt exist, it returns 0
		irr::f32 joystickAxisPos(irr::s32 axis, irr::f32 deadzone = 0.05f, irr::u8 joystick = 0);

		// Did a gui event regarding the particular gui id occur? if you don't specify the event type you're searching for, it will just repond yes/no to whether an event happened as a whole with your specified gui id
		bool onGUI(irr::s32 id, irr::gui::EGUI_EVENT_TYPE type = irr::gui::EGET_COUNT);
		

	protected:


	private:
		Core *_core;
		
		int setupStates();
		int setupJoysticks();
		
		void processKey(const irr::SEvent &event);
		void processMouse(const irr::SEvent &event);
		void processJoystick(const irr::SEvent &event);
		void processGUI(const irr::SEvent &event);

		std::unordered_map<irr::s32, KeyState> _keyStates;
		std::unordered_map<MouseButton, KeyState> _mouseButtonStates;
		
		irr::core::dimension2d<irr::s32> _mousePos = {0, 0};
		irr::f32 _mouseScrolled = 0.0f;

		// irrlicht's createJoysticks() needs to take in one o' their fanciful custom array types, :(((
		irr::core::array<irr::SJoystickInfo> _joysticks{};
		// Joysticks and gui events need to be narrowed down further if you want their useful information
		irr::SEvent::SJoystickEvent _joystickEvent;

		irr::SEvent::SGUIEvent _guiEvent;

	};
}