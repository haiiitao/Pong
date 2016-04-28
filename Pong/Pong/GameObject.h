#pragma once

#include <string>
#include <time.h>
#include "Sprite.h"
#include "Texty.h"
#include "EventListener.h"

namespace GE161
{
	class GameObject : public EventListener
	{
		friend class Texty;
	public:
		GameObject();
		virtual ~GameObject();
		/*********************************************************************************/
		// <GameObject.h>
		// I have changed GameObject class inherited from EventListener
		// the implementation of update() should be implemented by Game Objects
		virtual void update() = 0;
		// every Object should implement their own setup()
		virtual void setup(std::string object, std::string sheet, int startingX = 0, int startingY = 0) = 0;
		// to let Object access to its' sprite sheet name
		std::string sheetName;

		// implementation for virtual method from EventListener
		virtual void setup() {}
		virtual void draw() {}

		int xFrame;
		int yFrame;

		int x_delta, y_delta;

		void setPos(int x, int y);
		void moveX(int delta);
		void moveY(int delta);
		int getX();
		int getY();
		void attachSprite(Sprite* sprite);
		void draw(int frameIndex);
		void draw(std::string sequenceName);

		// overlapWith() for ball and paddle/character
		bool overlapWith(GameObject* otherGameObject);
		// Since the bounce of the Bomb and the Ball does not work well
		// everytime just the ball bounces, the bomb remain its route
		// so I override the ovelapWith() to let both of them bounce when they meet eachother
		bool overlapWith(GameObject* otherGameObject, bool bounce);

		// <GameObject.h>
		// Fun() implement the reaction of the overlaps of Characters and treatures
		bool Fun(std::vector<GE161::GameObject* > f);

		// I override the BounceoffScreen() to make another movement pattern for the Paddle
		// And I add a boolean parameter in the old version of BounceofScreen
		// to distinguish the action of BounceofScreen between the Bomb and the Ball
		bool BounceoffScreen(bool t);
		bool BounceoffScreen();
		bool offScreen();

		bool up = false, down = false, left = false, right = false;

		// write text here
		// for GamePlay Scene
		void writeText();
		// for Instruction Scene
		void writeText(std::string content);

	private:
		int x_;		// current position of
		int y_;		// this game object

		Sprite* sprite_;
		Texty* text;
	};
}

