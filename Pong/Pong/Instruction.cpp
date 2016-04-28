#include "Instruction.h"

GE161::Instruction::Instruction(Pong * pong):
	theGame(pong)
{
}

GE161::Instruction::~Instruction()
{
}

void GE161::Instruction::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(50, 50);
	xFrame = 450;
	yFrame = 300;
	sheetName = sheet;
	objectName = object;

	GE161::Sprite* instructionsImage = new GE161::Sprite(xFrame, yFrame);
	frameIndex = instructionsImage->makeFrame(GE161::Game::basePath() + "Instructions.png", 0, 0);
	attachSprite(instructionsImage);

}

void GE161::Instruction::update()
{
	draw(frameIndex);
}

