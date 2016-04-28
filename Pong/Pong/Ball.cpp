#include "Ball.h"


GE161::Ball::Ball(Pong* pong):
	theGame(pong)
{
}

GE161::Ball::~Ball()
{
}

void GE161::Ball::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	xFrame = 64;
	yFrame = 64;
	sheetName = sheet;
	objectName = object;
	//ball = new GE161::Ball(frameWidth_, frameHeight_, theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
	GE161::Sprite* ballSpriteSheet = new GE161::Sprite(xFrame, yFrame);

	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			int f = ballSpriteSheet->makeFrame(
				GE161::Game::basePath() + "RollingBall.png",
				column*xFrame, row*yFrame);
			ballSpriteSheet->addFrameToSequence(sheetName, f);
		}
	}
	attachSprite(ballSpriteSheet);

	x_delta = y_delta = 1;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
}


void GE161::Ball::update()
{
	moveX(x_delta);
	moveY(y_delta);
}

void GE161::Ball::onEvent(Event & event)
{
	if (event.type == GE161::Event::KEY_DOWN)
	{
		if (event.key == "BACKSPACE")
		{
			setPos(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
		}
	}
}
