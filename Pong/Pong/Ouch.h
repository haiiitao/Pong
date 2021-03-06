#pragma once
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\GameObject.h"
#include "C:\Users\HAITAO ZHU\Desktop\SDL\GE161v1\Pong.h"

namespace GE161
{
	class Ouch :
		public GameObject
	{
	public:
		Ouch(Pong* pong);
		~Ouch();

		void setup(std::string object, std::string sheet, int startingX = 0, int startingY = 0);
		void update();

		// Override EventListener method.
		void onEvent(Event& ev);

	private:
		std::string objectName;
		Pong* theGame;
	};
}

