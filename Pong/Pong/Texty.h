// Texty.h

#pragma once

#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"

namespace GE161
{
	class Texty
	{
		friend class Sprite;

	public:
		Texty(SDL_Renderer* renderer, std::string fontName, int fontSize = 10, bool visible = true);
		~Texty();

		enum writeOption_t { CONTINUE, NEXT_LINE };

		void write(std::string text, writeOption_t option = Texty::CONTINUE);

		void write(std::string text, int x, int y);


	private:
		/* To be coded for Homework 4. */
		SDL_Renderer* renderer;
		SDL_Texture* Message;
		SDL_Color fontColor;
		TTF_Font* font;

		bool visible;
		int NextX, NextY;
		int LineStart; // mark the position of the start(x coordinate) of each line

		void writeText(std::string text);
	};
}