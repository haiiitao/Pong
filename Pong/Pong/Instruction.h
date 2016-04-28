#pragma once
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\GameObject.h"
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\Pong.h"

namespace GE161
{
	class Instruction :
		public GameObject
	{
	public:
		Instruction(Pong* pong);
		~Instruction();

		void setup(std::string object, std::string sheet, int startingX = 0, int startingY = 0);
		void update();

	private:
		std::string objectName;
		Pong* theGame;
		int frameIndex;
	};
}
