
#include <string>
#include "Pong.h"
#include "Ball.h"
#include "Paddle.h"
#include "Character.h"
#include "Icons.h"
#include "Ouch.h"
#include "Bomb.h"
#include "Instruction.h"
#include "PongInstructionsScene.h"
#include "PongGamePlayScene.h"

// Pong.cpp

//An object of the class derived from GE161::Game must be created.
Pong* theGame = new Pong();

// setup() is called once, before the window is created or displayed.
void Pong::setup()
{
	window()->size(640, 480);
	window()->title("Pong");

	addScene("Instructions", new PongInstructionsScene(this));
	addScene("GamePlay", new PongGamePlayScene(this));
	// <Pong.cpp> setup()
	// I add instruction and other game objects here to let the game can access the objects
	addInstruction("Instruction", "Instruction", new GE161::Instruction(this));

	addObject("Ball", "Rolling", new GE161::Ball(this));
	addObject("paddle", "paddle", new GE161::Paddle(this));
	addObject("character", "character", new GE161::Character(this));
	addObject("Ouch", "Ouch", new GE161::Ouch(this));
	addObject("Bomb", "Bomb", new GE161::Bomb(this));

	std::string iconName[] = { "Ring", "Neckless", "Crown", "Cure" };
	std::vector<std::pair <int, int>> iconPos = { { 130, 133 },{ 342, 88 },{ 421, 54 },{ 260, 295 } };
	for (int i = 0; i < 4; i++)
	{
		addObject(iconName[i], iconName[i], new GE161::Icons(this, iconPos[i].first, iconPos[i].second));
	}
}

std::string Pong::chooseScene(std::string prevScene, int prevReturnCode)
{
	if (prevScene == START_GAME)
	{
		return "Instructions";
	}
	else if (prevScene == "Instructions" && prevReturnCode > 0)
	{
		return "GamePlay";
	}
	// prevScene must == "GamePlay"
	return EXIT_GAME;
}


