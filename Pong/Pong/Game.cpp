#include "Game.h"

const std::string GE161::Game::START_GAME = "*STARTGAME*";
const std::string GE161::Game::EXIT_GAME = "*EXITGAME*";

//The linker wants this static variable defined here; it will get
// its actual value in main().
GE161::Game* GE161::Game::theGame = nullptr;

GE161::Game::Game()
{
	// Store a pointer to the game in a static variable for access by main().
	if (theGame == nullptr)
	{
		theGame = this;
	}
	else
	{
		fatalSDLError("More than one game object has been created.");
	}
	// HW8
	// <Game.cpp> constructor
	bounceRight_ = 0;
	bounceLeft_ = 0;
	score = 0;
	coin = 0;
	life = 3;
	exitGamePlay = false;
	pick = false;
	icon = false;
	penalty = false;
	collision = false;
	text = false;
	playGameRequested = false;
	exitRequested = false;
	setupSuccess = false;
	setupGameSuccess = false;
	code = CONTINUE_SCENE;
}


GE161::Game::~Game()
{
}

void GE161::Game::BackgroundColor(Window* win, int r, int g, int b)
{
	int rc = SDL_SetRenderDrawColor(win->sdl_renderer, r, g, b, SDL_ALPHA_OPAQUE);
	if (rc != 0)
	{
		fatalSDLError("In Window::clearBackground(), SDL_SetRenderDrawColor returned non-zero: ", SDL_GetError());
		return;
	}
	rc = SDL_RenderClear(win->sdl_renderer);
	if (rc != 0)
	{
		fatalSDLError("In Window::clearBackground(), SDL_RenderClear returned non-zero: ", SDL_GetError());
		return;
	}
}

// *HW8*
// <Game.cpp> the implementation of sendEvent()
void GE161::Game::sendEvent(int type)
{
	theGame->eventQueue_->eventQueue_.push(new GE161::Event(type));
}

void GE161::Game::addScene(std::string name, GE161::EventListener* scene)
{
	sceneMap[name] = scene;
}

GE161::EventListener* GE161::Game::lookUpScene(std::string name)
{
	if (sceneMap.count(name) == 1)
		return sceneMap[name];

	fatalSDLError("in Game::lookUpScene, scene name not found:", name);

	return nullptr;
}

SDL_Renderer* GE161::Game::getRenderer()
{
	return window_->sdl_renderer;
}

void GE161::Game::delay(int milliseconds)
{
	if (milliseconds <= 0)
		return;
	SDL_Delay(static_cast<unsigned int>(milliseconds));
}

std::string GE161::Game::pathSlash()
{
#ifdef _WIN32
	return std::string("\\");
#else
	return std::string("/");
#endif
}

int GE161::Game::getTicks()
{
	return static_cast<int>(SDL_GetTicks());
}

void GE161::Game::registerAsListener(int eventType, EventListener* listener)
{
	theGame->eventQueue_->registerAsListener(eventType, listener);
}



// Based on res_path.h.
std::string GE161::Game::basePath()
{
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty())
	{
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else
		{
			fatalSDLError("error in Game::basePath", SDL_GetError());
			baseRes = "";
		}
	}
	return baseRes;
}

void GE161::Game::debugOut(std::string message)
{
	OutputDebugString((message + "\n").c_str());
}

GE161::Window* GE161::Game::window()
{
	return window_;
}

GE161::World * GE161::Game::world()
{
	return world_;
}


/***********************************************************************************/
// <Game.cpp>
// the implementation of addObject() and addInstruction()
void GE161::Game::addObject(std::string objectName, std::string sheet, GameObject * object)
{
	world_->objectMap[objectName] = object;
	world_->objectMap[objectName]->sheetName = sheet;
	theGame->world_->ObjectName.push_back(objectName);
}

void GE161::Game::addInstruction(std::string objectName, std::string sheet, GameObject * object)
{
	world_->Instruction = object;
	world_->Instruction->sheetName = sheet;
}


GE161::GameObject * GE161::Game::lookUpObject(std::string name)
{
	if (world_->objectMap.count(name) == 1)
		return world_->objectMap[name];

	fatalSDLError("in Game::lookUpObject, object name not found:", name);

	return nullptr;
}
