#pragma once
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\GameObject.h"
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\Pong.h"

namespace GE161
{
	class Icons :
		public GameObject
	{
	public:
		Icons (Pong* pong, int startx, int starty);
		~Icons();

		void setup(std::string object, std::string sheet, int startingX = 0, int startingY = 0);
		void update();

	private:
		//std::vector<std::pair<GE161::GameObject*, std::string >> treatures;
		int startX, startY;
		std::string objectName;
		Pong* theGame;
	};
}

