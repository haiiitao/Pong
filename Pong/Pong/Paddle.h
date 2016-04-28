#pragma once
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\GameObject.h"
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\Pong.h"

namespace GE161
{
	class Paddle :
		public GameObject
	{
	public:
		Paddle(Pong* pong);
		~Paddle();

		void setup(std::string object, std::string sheet, int startingX = 0, int startingY = 0);
		void update();

	private:
		std::string objectName;
		Pong* theGame;
	};
}

