#include "PongGamePlayScene.h"
#include "Event.h"
#include "Texty.h"

#include <stdlib.h>		// srand, rand
#include <time.h>		// time



//PongGamePlayScene.cpp

PongGamePlayScene::PongGamePlayScene(Pong* pong) :
	theGame(pong)
{

}

PongGamePlayScene::~PongGamePlayScene()
{

}
/**********************************************************************************/
// <PongGamePlayScene.cpp>
// Corresponding changes to adding class Ball, Bomb, etc.
void PongGamePlayScene::setup()
{
	std::vector<std::string> objectname = GE161::Game::theGame->getObjectName();

	for (int i = 0; i < objectname.size(); i++)
	{
		GE161::GameObject* Gobject = GE161::Game::theGame->world()->objectMap[objectname[i]];
		Gobject->setup(objectname[i], Gobject->sheetName);
	}

	// seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(NULL)));

	// 30 fps
	theGame->framesPerSecond = 30;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);

	GE161::Game::theGame->setupGameSuccess = true;
}

void PongGamePlayScene::draw()
{
	std::vector<std::string> objectname = GE161::Game::theGame->getObjectName();

	for (int i = 0; i < objectname.size(); i++)
	{
		GE161::GameObject* Gobject = GE161::Game::theGame->world()->objectMap[objectname[i]];
		if (objectname[i] != "Ouch")
		{
			Gobject->draw(Gobject->sheetName);
			// distinguish the BounceofScreen between Ball and Bomb
			if (objectname[i] == "Ball")
			{
				Bal = Gobject;
			}
			else if (objectname[i] == "Bomb")
			{
				Bom = Gobject;
			}
			else if (objectname[i] == "paddle")
			{
				Pad = Gobject;
				Gobject->BounceoffScreen();
			}
			else if (objectname[i] == "character")
			{
				Chara = Gobject;
				Gobject->offScreen();
			}
			else if (objectname[i] == "Ring" || objectname[i] == "Neckless" || objectname[i] == "Crown" || objectname[i] == "Cure")
			{
				treat.push_back(Gobject);
			}
		}
		else
		{
			Ouc = Gobject;
		}
	}

	Bal->BounceoffScreen(true);
	Bom->BounceoffScreen(false);
	Bal->overlapWith(Chara);
	Bal->overlapWith(Bom, Bal);
	Bom->overlapWith(Pad);

	if (Bal->overlapWith(Pad))
	{
		GE161::Game::theGame->score++;
		if (GE161::Game::theGame->collision)
		{
			Ouc->setPos((Bal->getX() + Pad->getX()) / 2, (Bal->getY() + Pad->getY()) / 2);
			Ouc->draw(Ouc->sheetName);
		}
	}
	if (Bom->overlapWith(Chara))
	{
		Bom->setPos(rand() % 600 + 1, rand() % 400 + 1);
		GE161::Game::theGame->life--;
		if (GE161::Game::theGame->life < 0)
		{
			GE161::Game::theGame->exitGamePlay = true;
		}
	}

	GE161::Game::theGame->icon = Chara->Fun(treat);
	// handle the collision of Paddle and Ball

	if (GE161::Game::theGame->bounceRight_ >= 20)
	{
		GE161::Game::theGame->code = -1;
	}
	else if (GE161::Game::theGame->exitGamePlay)
	{
		GE161::Game::theGame->code = -1;
	}
	else
	{
		GE161::Game::theGame->code = 0;
	}
}

void PongGamePlayScene::onEvent(GE161::Event & event)
{
	if (event.type == GE161::Event::KEY_DOWN)  // this test isn't necessary
	{
		if (event.key == "X")
		{
			GE161::Game::theGame->exitGamePlay = true;
		}
	}
}
