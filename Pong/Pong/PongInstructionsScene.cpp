// PongInstructionScene.cpp

#include "PongInstructionsScene.h"
#include "Event.h"
#include "Game.h"

PongInstructionsScene::PongInstructionsScene(Pong* game) :
	theGame(game)
{
}

PongInstructionsScene::~PongInstructionsScene()
{
	delete instructions;
}

// <PongInstructionsScene.cpp>
// Corresponding changes to the adding class of Instruction
void PongInstructionsScene::setup()
{
	instructions = GE161::Game::theGame->world()->Instruction;
	instructions->setup("Instruction", "Instruction");

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	GE161::Game::debugOut("PongInstructionsScene::setup completed!");
	GE161::Game::theGame->setupSuccess = true;
}

void PongInstructionsScene::draw()
{
	instructions->update();
	instructions->writeText("Hey follow the instruction below");

	if (GE161::Game::theGame->playGameRequested)
	{
		GE161::Game::theGame->code = 1;		// don't call draw again, go on to next scene
	}
	else if (GE161::Game::theGame->exitRequested)
	{
		GE161::Game::theGame->code = -1;		// stop program
	}
	else
	{
		GE161::Game::theGame->code = 0;
	}
}

void PongInstructionsScene::onEvent(GE161::Event& event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == " ")
		{
			GE161::Game::theGame->text = true;
			GE161::Game::theGame->playGameRequested = true;
		}
		else if (event.key == "X")
		{
			GE161::Game::theGame->exitRequested = true;
		}
	}
}

