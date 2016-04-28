#pragma once

#include "Event.h"

namespace GE161
{
	class EventListener
	{
	public:
		EventListener();

		// This method should be overridden by derived classes that
		// want to receive events.
		virtual void onEvent(Event& ev);
		/***************************************************************************************/
		// <EventListener.h>
		// I have moved setip() and draw() from Scene.h to here
		// then I changed the inheritance of PongInstructionsScene and PongGamePlayScene
		// from Scene to EventListener
		virtual void setup() = 0;
		virtual void draw() = 0;
	};

}
