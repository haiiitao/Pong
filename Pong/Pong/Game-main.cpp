#include "Game.h"

void GE161::Game::main(int x)
{
	if (x != 8675309)
	{
		fatalSDLError("Do not invoke GE161::Game::main()");
		return;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fatalSDLError("SDL_Init(SDL_INIT_EVERYTHING) Error in main(): ", SDL_GetError());
		return;
	}

	// Invoke the game's overridden setup() method, and create the SDL window.
	window_ = new GE161::Window();
	/***********************************************************************/
	// <Game-main.cpp>
	// initialize the world_
	// otherwise we cannot operate the operations like ObjectMap of World Class
	world_ = new GE161::World();
	setup();

	window_->initialize();
	window_->clearBackground();
	//theGame->BackgroundColor(window_, 0, 0, 0);

	eventQueue_ = new GE161::EventQueue();

	std::string sceneName = GE161::Game::START_GAME;
	//int returnCode = code;

	// Loop through the outer while loop once per scene.
	// A negative return code from a scene says "Stop the program!"

	// <Game-main.cpp>
	// Outer Loop per scene
	while (code >= 0)
	{
		// Ask the game which scene to do next.
		sceneName = GE161::Game::theGame->chooseScene(sceneName, code);
		GE161::EventListener* scene = GE161::Game::theGame->lookUpScene(sceneName);

		// Now we have the scene to use.  First, run its setup().
		// because of the void setup() 
		// I need to distinguish the setup() success from instruction and Gameplay
		scene->setup();
		bool success;
		if (sceneName == "Instructions")
		{
			success = theGame->setupSuccess;
		}
		else if (sceneName == "GamePlay")
		{
			success = theGame->setupGameSuccess;
		}
		if (!success)
		{
			fatalSDLError("error in main(), setup failed for scene", sceneName);
			return;
		}

		// setup() succeeded.  Run its draw() until a non-zero return code.
		code = GE161::Game::CONTINUE_SCENE;

		// I have changed the inner loop to world_ class
		theGame->world_->gameLoop(code, scene);

		std::string m = std::string("return code from ") + sceneName + std::string(": ") + std::to_string(code);
		debugOut(m);

	}
	SDL_Quit();
	return;
}

GE161::World::World()
{
}

// <Game-main.cpp>
// the inner loop
void GE161::World::gameLoop(int returnCode, GE161::EventListener* scene)
{
	// Loop through the inner while loop once per frame in scene.
	// array to store frame counter
	int array[5];
	int i = 0;
	double average = 0;
	double last = 0, current;

	// <Game-main.cpp>
	// the inner loop from void GE161::World::gameLoop()
	while (returnCode == GE161::Game::CONTINUE_SCENE)
	{
		// text is a signal to mark the text to draw on the Instruction or GamePlay Scene
		if (GE161::Game::theGame->text)
		{
			if (GE161::Game::theGame->penalty)
			{
				GE161::Game::theGame->sendEvent(GE161::Event::bouncePenalty);
			}
			GE161::Game::theGame->sendEvent(GE161::Event::collision);
		}
		GE161::Game::theGame->eventQueue_->getSDLEvents();
		GE161::Game::theGame->eventQueue_->callEventListeners();

		GE161::Game::theGame->window_->clearBackground();
		//GE161::Game::theGame->BackgroundColor(GE161::Game::theGame->window_, 0, 0, 0);
		std::vector<std::string> objectname = GE161::Game::theGame->getObjectName();

		scene->draw();
		returnCode = GE161::Game::theGame->code;
		// update each Object per frame
		for (int i = 0; i < int(objectname.size()); i++)
		{
			objectMap[objectname[i]]->update();
		}

		GE161::Game::theGame->window_->drawToScreen();

		// counter increase every frame
		GE161::Game::theGame->counter++;

		current = GE161::Game::theGame->getTicks();
		if (current > last + 1000)
		{
			array[i] = GE161::Game::theGame->counter;
			GE161::Game::theGame->counter = 0;
			last = current;
			i++;
		}
		if (i == 5)
		{
			average = (array[0] + array[1] + array[2] + array[3] + array[4]) / 10;
			for (int j = 1; j < 5; j++)
			{
				array[j - 1] = array[j];
			}
			i--;
		}
		int r;
		if (average)
		{
			r = int(average);
		}
		else
		{
			r = GE161::Game::theGame->framesPerSecond;
		}

		GE161::Game::theGame->delay(GE161::Game::theGame->framesPerSecond);
		std::string report = std::string("frames per second ") + std::string(": ") + std::to_string(r);
		debugOut(report);

	}
}

std::vector<std::string> GE161::Game::getObjectName()
{
	return theGame->world_->ObjectName;
}


