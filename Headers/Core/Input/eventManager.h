#pragma once

#include <irrlicht.h>

// Event manager, and an event component which your "event-wanting" objects can comprise of
namespace Sping
{
	class Core;

	struct MouseInfo
	{
		irr::core::dimension2d<irr::s32> pos;

	};

	class EventManager : public irr::IEventReceiver
	{
	public:
		EventManager();
		~EventManager();

		int init(Core *core);
		
		virtual bool OnEvent(const irr::SEvent &event);
		
		bool isKeyDown(irr::EKEY_CODE keycode);
		bool isKeyUp(irr::EKEY_CODE keycode);
		bool isKeyHeld(irr::EKEY_CODE keycode);
		
		bool isMouseDown(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool isMouseUp(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool isMouseHeld(irr::E_MOUSE_BUTTON_STATE_MASK button);
		
		bool isMouseDoubleClick(irr::E_MOUSE_BUTTON_STATE_MASK button);
		bool isMouseTripleClick(irr::E_MOUSE_BUTTON_STATE_MASK button);

		bool isMouseMoved();
		bool isMouseScrolled();

		irr::core::dimension2d<irr::s32> mousePos();

	protected:


	private:
		Core *_core;

	};
}