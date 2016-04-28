#include "Icons.h"

GE161::Icons::Icons(Pong * pong, int startx, int starty):
	theGame(pong), startX(startx), startY(starty)
{
}

GE161::Icons::~Icons()
{
}

void GE161::Icons::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(rand() % 640 + 1, rand() % 480 + 1);
	xFrame = 32;
	yFrame = 32;
	sheetName = sheet;
	objectName = object;
	// add some icons
	//Ring = new GE161::GameObject(32, 26, rand() % 640 + 1, rand() % 640 + 1);
	GE161::Sprite* IconSheet = new GE161::Sprite(xFrame, yFrame);
	IconSheet->addFrameToSequence(sheetName, IconSheet->makeFrame(GE161::Game::basePath() + "icons.png", startX, startY));
	attachSprite(IconSheet);
}

void GE161::Icons::update()
{
	if (GE161::Game::theGame->pick && GE161::Game::theGame->icon)
	{
		setPos(rand() % 600 + 1, rand() % 400 + 1);
	}
}
