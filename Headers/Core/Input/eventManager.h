#pragma once

#include <irrlicht.h>
#include <functional>

// Event manager, and an event component which your "event-wanting" objects can comprise of
namespace Sping
{
	class Core;

	class EventObserver
	{
	public:
		EventObserver();
		~EventObserver();

	protected:


	private:
		friend class EventManager;

		std::function<void(void)> _function;

		irr::s32 _eventType;
		irr::s32 _eventEnum;

	};

	class EventManager : public irr::IEventReceiver
	{
	public:
		EventManager();
		~EventManager();

		int init(Core *core);
		
		virtual bool OnEvent(const irr::SEvent &event);

		// Subscribe your event observer (which you've set up to trigger your desired function upon your desired event occuring)
		int operator+=(EventObserver *subscriber);

		// Unsubscribe :(
		int operator-=(EventObserver *subscriber);

	protected:


	private:
		Core *_core;
		//TODO: arrays of input types http://irrlicht.sourceforge.net/docu/namespaceirr.html, which then contain arrays to call observer funcs which have subscribed to it (reference the mouse & joystick guide for handling it)
		

	};
}