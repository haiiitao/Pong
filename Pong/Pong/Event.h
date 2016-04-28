#pragma once

#include <queue>
#include <string>
#include "GE161int.h"

namespace GE161
{
	class Event
	{
		friend class EventQueue;

	public:
		Event();
		Event(SDL_Event& e);
		// *HW8*
		Event(int type);
		~Event();

		// These fields are public for convenient access.
		int type;
		std::string key;
		int mouseButton;
		int mouseClicks;
		int x;
		int y;

		// event types
		static const int QUIT = SDL_QUIT;
		static const int KEY_DOWN = SDL_KEYDOWN;
		static const int KEY_UP = SDL_KEYUP;
		static const int MOUSE_MOTION = SDL_MOUSEMOTION;
		static const int MOUSE_BUTTONDOWN = SDL_MOUSEBUTTONDOWN;
		static const int MOUSE_BUTTONUP = SDL_MOUSEBUTTONUP;
		// <Event.h> create new Event types
		static const enum myEvent
		{
			collision = 1, bouncePenalty = 2
		};


	private:
		SDL_Event sdl_event;

	};

}