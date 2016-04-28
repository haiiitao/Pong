#include "Bomb.h"

GE161::Bomb::Bomb(Pong * pong):
	theGame(pong)
{
}

GE161::Bomb::~Bomb()
{
}

void GE161::Bomb::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(rand() % 640 + 1, rand() % 480 + 1);
	xFrame = 34;
	yFrame = 31;
	sheetName = sheet;
	objectName = object;

	GE161::Sprite* BoomSheet = new GE161::Sprite(xFrame, yFrame);
	BoomSheet->addFrameToSequence(sheetName, BoomSheet->makeFrame(GE161::Game::basePath() + "icons.png", 380, 214));
	attachSprite(BoomSheet);

	// for Boom and paddle's movement
	x_delta = y_delta = 1;
}

void GE161::Bomb::update()
{
	moveX(x_delta);
	moveY(y_delta);
}
