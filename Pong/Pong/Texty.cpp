// Texty.cpp
/* Check if there is the specified font
if (this->font == NULL)
std::cout << "Open Font Error: " << TTF_GetError() << std::endl;

TTF_GetError()
It returns the last error set by TTF_SetError (or SDL_SetError) as a string.
Use this to tell the user what happened when an error status has been returned from an SDL_ttf function call.
*/
#include "Texty.h"   // You can add or remove #include files as needed.
#include <iostream>
#include <sstream>
#include "Windows.h"
#include <string>


void renderTexture2(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Setup the destination rectangle to be at the position we want 
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture2(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect dst, SDL_Rect *clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture2(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}
	renderTexture2(tex, ren, dst, clip);
}


GE161::Texty::Texty(SDL_Renderer * renderer, std::string fontName, int fontSize, bool visible)
{
	// initialize SDL_ttf
	if (TTF_Init() == -1)
		std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
	this->renderer = renderer;

	this->font = TTF_OpenFont(fontName.c_str(), fontSize);
	// Check if there is the specified font
	if (this->font == NULL)
		std::cout << "Open Font Error: " << TTF_GetError() << std::endl;

	this->visible = visible;
	if (visible)
		this->fontColor = { 0, 100, 255, 0 };
	else
		this->fontColor = { 0, 0, 0, 0 };
}

GE161::Texty::~Texty()
{
	TTF_CloseFont(font);
}

void GE161::Texty::write(std::string text, writeOption_t option)
{
	if (option == Texty::NEXT_LINE)
	{
		NextX = LineStart;
		NextY = NextY + TTF_FontHeight(font);
	}

	if (text != "")
		writeText(text);
}

void GE161::Texty::write(std::string text, int x, int y)
{
	LineStart = x;
	NextX = x;
	NextY = y;

	if (text != "")
		writeText(text);
}

void GE161::Texty::writeText(std::string text)
{
	int width;
	// get the width of a string 

	TTF_SizeText(font, text.c_str(), &width, nullptr);

	SDL_Surface* fontSurface = TTF_RenderText_Blended(font, text.c_str(), fontColor);
	Message = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	renderTexture2(Message, renderer, NextX, NextY);
	// to continue current line, recaculate the NextX to avoid overlapped
	NextX = NextX + width;
}
