#pragma once

#include <string>
#include <map>
#include "Window.h"
#include "Scene.h"
#include "GameObject.h"
#include "EventQueue.h"
//#include "Texty.h"

namespace GE161
{
	class Game
	{
		friend class Sprite;
		friend class GameObject;
		friend class Window;
		friend class World;
	public:
		Game();
		~Game();

		int framesPerSecond;

		void BackgroundColor(Window* win, int r, int g, int b);

		/*******************************************************************************************/
		// These functions are called by the game code.
		// <Game.h> Public
		// Since I have moved the Scene.h
		// I have changed all Scene Object to EventListener Object
		void addScene(std::string name, EventListener* scene);
		EventListener* lookUpScene(std::string name);
		Window* window();

		// addObject(), addInstruction() are for GameObjects like Ball and Instruction Scene
		World* world();
		void addObject(std::string objectName, std::string sheet, GameObject* object);
		void addInstruction(std::string objectName, std::string sheet, GameObject* object);
		GameObject* lookUpObject(std::string name);
		// this method provide access to Objects' name that pushed into ObjectMap
		std::vector<std::string > getObjectName();

		static void registerAsListener(int eventType, EventListener* listener);

		// Helpful functions exposed to the game programmer.
		static void delay(int milliseconds);
		static std::string pathSlash();
		static std::string basePath();
		static void debugOut(std::string);
		static int getTicks();

		// These functions have to be overridden by the game code.
		virtual void setup() = 0;
		virtual std::string chooseScene(std::string prevScene, int prevReturnCode) = 0;

		// This function should be called exactly once by main().
		void main(int x);


		static const std::string START_GAME;
		static const std::string EXIT_GAME;

		bool playGameRequested;
		bool exitRequested;

		static Game* theGame;
		static const int CONTINUE_SCENE = 0;

		// *HW8* 
		// <Game.h>
		// sendEvent() to send the new Event Type
		void sendEvent(int type);
		// count the bounce times of left and right
		// every time the Ball bounce the left side of screen, sendEvent(bouncePenalty)
		// when bounce the right side of screen 20 times, exit game
		int bounceLeft_;
		int bounceRight_;
		// score records the times the Ball hits the Paddle
		int score;
		// coin records the Gold
		int coin;
		// life initial as 3
		// life-- when the Character encounters the Bomb
		// life++ when the Character pick the Red Liquid
		int life;
		// exitGamePlay turned be true when (life < 0 || press "X")
		bool exitGamePlay;
		// pick marks the "F" keyDown or keyUp to pick up treasrues
		bool pick;
		bool icon;
		// penalty decide if sendEvent(bouncePenalty)
		bool penalty;
		bool collision;
		// for text
		bool text;
		//*********HW9***********
		// <Game.h> Public
		// Since I have moved Scene.h, and changed 
		// bool setup() and int draw() to void()
		// I have to distinguish the success build of InstructionScene and PlayScene
		bool setupSuccess;
		bool setupGameSuccess;
		// And also I have to change the retrunCode to be a parameter of Game.h
		// to mark the retrunCode from int draw() in the former version
		int code;

	private:
		SDL_Renderer* getRenderer();
		int counter = 0;

		Window* window_;
		std::map<std::string, EventListener*> sceneMap;
		EventQueue* eventQueue_;
		/***********************************************************************************/
		// <Game.h> private
		// to access parameters in World class
		World* world_;
	};
	// <Game.h>
	class World
	{
		friend class Game;
	public:
		World();
		// World GameLoop
		void gameLoop(int returnCode, EventListener* scene);

		// mark the Objects and Instruction
		std::map<std::string, GameObject* > objectMap;
		GameObject* Instruction;
	private:
		// to store the Object name
		std::vector<std::string > ObjectName;
	};

}
