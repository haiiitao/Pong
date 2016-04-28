#include "Paddle.h"

GE161::Paddle::Paddle(Pong * pong):
	theGame(pong)
{
}

GE161::Paddle::~Paddle()
{
}

void GE161::Paddle::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(theGame->window()->clientWidth() / 4, theGame->window()->clientHeight() / 2);
	xFrame = 10;
	yFrame = 65;
	sheetName = sheet;
	objectName = object;

	// add paddlesheet
	//paddle = new GE161::GameObject(10, 65, theGame->window()->clientWidth() / 4, theGame->window()->clientHeight() / 2);
	GE161::Sprite* paddleSheet = new GE161::Sprite(xFrame, yFrame);
	paddleSheet->addFrameToSequence(sheetName, paddleSheet->makeFrame(GE161::Game::basePath() + "paddle.png",
		235, 127));
	attachSprite(paddleSheet);

	x_delta = 0;
	y_delta = 2;
}

void GE161::Paddle::update()
{
	moveY(y_delta);
}
