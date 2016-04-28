//PongGamePlayScene.h

#pragma once

#include "Pong.h"
#include "Scene.h"
#include "Event.h"
#include "Texty.h"

#include "GameObject.h"

class PongGamePlayScene : public GE161::EventListener
{
public:
	PongGamePlayScene(Pong* theGame);
	~PongGamePlayScene();

	void setup();
	void draw();

	void onEvent(GE161::Event & event);
private:
	Pong* theGame;

	//<PongGamePlayScene.h>
	// treat stores the object of treatures
	// Chara-character, Bal-ball, Bom-Bomb, Pad-paddle, Ouc-ouch
	std::vector<GE161::GameObject* > treat;
	GE161::GameObject* Chara;
	GE161::GameObject* Bal;
	GE161::GameObject* Bom;
	GE161::GameObject* Pad;
	GE161::GameObject* Ouc;

	int frameWidth_;
	int frameHeight_;
};

