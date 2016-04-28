#include "Character.h"

GE161::Character::Character(Pong* pong):
	theGame(pong)
{
}

GE161::Character::~Character()
{
}

void GE161::Character::setup(std::string object, std::string sheet, int startingX, int startingY)
{
	setPos(theGame->window()->clientWidth() / 3, theGame->window()->clientHeight() / 3);
	xFrame = 17;
	yFrame = 23;
	sheetName = sheet;
	objectName = object;

	// add a character
	//character = new GE161::GameObject(17, 23, theGame->window()->clientWidth() * 3 / 4, theGame->window()->clientHeight() / 2);
	GE161::Sprite* characterSheet = new GE161::Sprite(xFrame, yFrame);
	characterSheet->addFrameToSequence(sheetName, characterSheet->makeFrame(GE161::Game::basePath() + "Characters.png", 63, 7));
	characterSheet->addFrameToSequence("Character", characterSheet->makeFrame(GE161::Game::basePath() + "Characters.png", 63, 7));
	characterSheet->addFrameToSequence("WalkingCharacter", characterSheet->makeFrame(GE161::Game::basePath() + "Characters.png", 0, 10));
	characterSheet->addFrameToSequence("WalkingCharacter", characterSheet->makeFrame(GE161::Game::basePath() + "Characters.png", 47, 10));
	characterSheet->addFrameToSequence("pickIcon", characterSheet->makeFrame(GE161::Game::basePath() + "Characters.png", 95, 15));
	attachSprite(characterSheet);

	x_delta = y_delta = 0;

	GE161::Game::registerAsListener(GE161::Event::KEY_DOWN, this);
	// *HW8*
	// register these event type to the EventQueue
	GE161::Game::registerAsListener(GE161::Event::bouncePenalty, this);
	//	GE161::Game::registerAsListener(GE161::Event::collision, this);
	GE161::Game::registerAsListener(GE161::Event::KEY_UP, this);
}

void GE161::Character::update()
{

}

void GE161::Character::onEvent(Event & event)
{
	if (event.type == GE161::Event::KEY_DOWN) 
	{
		if (event.key == "DOWN")
		{
			if (!up)
			{
				moveY(3);
				sheetName = "Character";
			}
		}
		else if (event.key == "UP")
		{
			if (!down)
			{
				moveY(-3);
				sheetName = "Character";
			}
		}
		else if (event.key == "RIGHT")
		{
			if (!right)
			{
				moveX(3);
				sheetName = "WalkingCharacter";
			}
		}
		else if (event.key == "LEFT")
		{
			if (!left)
			{
				moveX(-3);
				sheetName = "WalkingCharacter";
			}
		}
		
		// press "F" to pick treasures
		else if (event.key == "F")
		{
			sheetName = "pickIcon";
			GE161::Game::theGame->pick = true;
		}
	}
	if (event.type == GE161::Event::KEY_UP)
	{
		if (event.key == "F")
		{
			sheetName = "Character";
			GE161::Game::theGame->pick = false;
		}
		else if (event.key == "RIGHT")
		{
			if (!right)
			{
				sheetName = "Character";
			}
		}
		else if (event.key == "LEFT")
		{
			if (!left)
			{
				sheetName = "Character";
			}
		}
	}
	if (event.type == GE161::Event::bouncePenalty)
	{
		setPos(theGame->window()->clientWidth() / 2, theGame->window()->clientHeight() / 2);
		GE161::Game::theGame->penalty = false;
	}
}

