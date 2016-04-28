#include "Ouch.h"

GE161::Ouch::Ouch(Pong * pong):
	theGame(pong)
{
}

GE161::Ouch::~Ouch()
{
}

void GE161::Ouch::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	xFrame = 72;
	yFrame = 51;
	sheetName = sheet;
	objectName = object;

	// add collision sheet
	//ouch = new GE161::GameObject(72, 51);
	GE161::Sprite* ouchSheet = new GE161::Sprite(xFrame, yFrame);
	ouchSheet->addFrameToSequence(sheetName, ouchSheet->makeFrame(GE161::Game::basePath() + "ouch.png", 0, 0));
	attachSprite(ouchSheet);

	GE161::Game::registerAsListener(GE161::Event::collision, this);
}

void GE161::Ouch::update()
{
}

void GE161::Ouch::onEvent(Event & event)
{
	// when the Ball bounce the left screen, character reset to the center of the Screen immediately
	// handle the collision Event
	if (event.type == GE161::Event::collision)
	{
		GE161::Game::theGame->collision = true;
	}
}
