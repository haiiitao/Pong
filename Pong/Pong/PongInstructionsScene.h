// PongInstructionsScene.h

#pragma once

#include "Pong.h"
#include "GameObject.h"
#include "Event.h"


class PongInstructionsScene : public GE161::EventListener
{
public:
	PongInstructionsScene(Pong* theGame);
	~PongInstructionsScene();

	// Override Scene methods.
	void setup();
	void draw();

	// Override EventListener method.
	void onEvent(GE161::Event& ev);
private:
	Pong* theGame;
	GE161::GameObject* instructions;
};

