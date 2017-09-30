/* 
This file implemented the most mechanisms of the game, since all objects presented in the game are inherited from GameObject. 
It incudes the objects' position, collisions for different objects and reactions after collisions, and also the renderer.
Not only those reactions we can see in the game, but also GameObject reflect the important attributes of virtual functions(might seen in Object implementation) and overload functions, which also gives the programmer--me a better understanding of how these attributes could inteact and perform and their advantages in real project.
*/
#include <time.h>
#include "GameObject.h"
#include "Game.h"


GE161::GameObject::GameObject() :
	x_(0),
	y_(0),
	sprite_(nullptr)
{
	//text = new Texty(GE161::Game::theGame->getRenderer(), GE161::Game::basePath() + "Aloha.ttf", 14, true);
}


GE161::GameObject::~GameObject()
{
}

void GE161::GameObject::setPos(int x, int y)
{
	x_ = x;
	y_ = y;
}

void GE161::GameObject::moveX(int delta)
{
	x_ += delta;
}

void GE161::GameObject::moveY(int delta)
{
	y_ += delta;
}

int GE161::GameObject::getX()
{
	return x_;
}

int GE161::GameObject::getY()
{
	return y_;
}

void GE161::GameObject::attachSprite(GE161::Sprite* sprite)
{
	sprite_ = sprite;
}

void GE161::GameObject::draw(int frameIndex)
{
	if (sprite_ == nullptr)
	{
		debugOut("GameObject::draw called, but no Sprite is attached.");
		return;
	}

	SDL_Rect srcrect = { sprite_->frames[frameIndex].x, sprite_->frames[frameIndex].y, sprite_->frameWidth_, sprite_->frameHeight_ };
	SDL_Rect destrect = { x_, y_, sprite_->frameWidth_, sprite_->frameHeight_ };
	if (GE161::Game::theGame->text)
	{
		writeText();
	}

	int success = SDL_RenderCopy(GE161::Game::theGame->getRenderer(), sprite_->frames[frameIndex].texture, &srcrect, &destrect);
	if (success != 0)
	{
		fatalSDLError("In GameObject::draw, SDL_RenderCopy: ", SDL_GetError());
	}
}

void GE161::GameObject::draw(std::string sequenceName)
{
	draw(sprite_->getNextFrameIndex(sequenceName));
}


bool GE161::GameObject::overlapWith(GameObject* otherGameObject)
{
	if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
	{
		if (otherGameObject->getY() >= getY() && otherGameObject->getY() <= getY() + yFrame)
		{
			x_delta = rand() % 3 + 1;
			return true;
		}
		else if (otherGameObject->getY() + otherGameObject->yFrame >= getY() && otherGameObject->getY() + otherGameObject->yFrame <= getY() + yFrame)
		{
			x_delta = rand() % 3 + 1;
			return true;
		}
	}
	if (getY() >= otherGameObject->getY() + otherGameObject->yFrame && getY() <= otherGameObject->getY() + otherGameObject->yFrame)
	{
		if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
		{
			y_delta = rand() % 3 + 1;
			return true;
		}
		else if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
		{
			y_delta = rand() % 3 + 1;
			return true;
		}
	}
	if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
	{
		if (otherGameObject->getY() >= getY() && otherGameObject->getY() <= getY() + yFrame)
		{
			x_delta = -(rand() % 3 + 1);
			return true;
		}
		else if (otherGameObject->getY() + otherGameObject->yFrame >= getY() && otherGameObject->getY() + otherGameObject->yFrame <= getY() + yFrame)
		{
			x_delta = -(rand() % 3 + 1);
			return true;
		}
	}
	if (getY() + yFrame >= otherGameObject->getY() && getY() + yFrame <= otherGameObject->getY() + otherGameObject->yFrame)
	{
		if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
		{
			y_delta = -(rand() % 3 + 1);
			return true;
		}
		else if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
		{
			y_delta = -(rand() % 3 + 1);
			return true;
		}
	}
	return false;
}


//<GameObject.cpp>
// Implementations for the adding functions
bool GE161::GameObject::overlapWith(GameObject* otherGameObject, bool bounce)
{
	if (bounce)
	{
		if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
		{
			if (otherGameObject->getY() >= getY() && otherGameObject->getY() <= getY() + yFrame)
			{
				x_delta = rand() % 3 + 1;
				otherGameObject->x_delta = -(rand() % 3 + 1);
				return true;
			}
			else if (otherGameObject->getY() + otherGameObject->yFrame >= getY() && otherGameObject->getY() + otherGameObject->yFrame <= getY() + yFrame)
			{
				x_delta = rand() % 3 + 1;
				otherGameObject->x_delta = -(rand() % 3 + 1);
				return true;
			}
		}
		if (getY() >= otherGameObject->getY() + otherGameObject->yFrame && getY() <= otherGameObject->getY() + otherGameObject->yFrame)
		{
			if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
			{
				y_delta = rand() % 3 + 1;
				otherGameObject->y_delta = -(rand() % 3 + 1);
				return true;
			}
			else if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
			{
				y_delta = rand() % 3 + 1;
				otherGameObject->y_delta = -(rand() % 3 + 1);
				return true;
			}
		}
		if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
		{
			if (otherGameObject->getY() >= getY() && otherGameObject->getY() <= getY() + yFrame)
			{
				x_delta = -(rand() % 3 + 1);
				otherGameObject->x_delta = rand() % 3 + 1;
				return true;
			}
			else if (otherGameObject->getY() + otherGameObject->yFrame >= getY() && otherGameObject->getY() + otherGameObject->yFrame <= getY() + yFrame)
			{
				x_delta = -(rand() % 3 + 1);
				otherGameObject->x_delta = rand() % 3 + 1;
				return true;
			}
		}
		if (getY() + yFrame >= otherGameObject->getY() && getY() + yFrame <= otherGameObject->getY() + otherGameObject->yFrame)
		{
			if (otherGameObject->getX() >= getX() && otherGameObject->getX() <= getX() + xFrame)
			{
				y_delta = -(rand() % 3 + 1);
				otherGameObject->y_delta = rand() % 3 + 1;
				return true;
			}
			else if (otherGameObject->getX() + otherGameObject->xFrame >= getX() && otherGameObject->getX() + otherGameObject->xFrame <= getX() + xFrame)
			{
				y_delta = -(rand() % 3 + 1);
				otherGameObject->y_delta = rand() % 3 + 1;
				return true;
			}
		}
	}
	return false;
}

// <GameObject.cpp> implementation of Fun()
// the first parameter of the pair is the GameObject, the second one is the spriteName
bool GE161::GameObject::Fun(std::vector<GE161::GameObject*> f)
{
	bool icon = false;
	for (auto p : f)
	{
		if (overlapWith(p) && GE161::Game::theGame->pick)
		{
			if (p->sheetName == "Ring")
			{
				GE161::Game::theGame->coin += 10;
			}
			else if (p->sheetName == "Neckless")
			{
				GE161::Game::theGame->coin += 5;
			}
			else if (p->sheetName == "Crown")
			{
				GE161::Game::theGame->coin += 15;
			}
			else if (p->sheetName == "Cure")
			{
				GE161::Game::theGame->life++;
			}
			icon = true;
			break;
		}
	}
	return icon;
}
// Ball->(true) to let bounceLeft and bounceRight increase
// Bomb->(false)
bool GE161::GameObject::BounceoffScreen(bool t)
{
	offScreen();
	bool bounce = false;
	if (left)
	{
		x_delta = rand() % 3 + 1;
		if (t)
		{
			GE161::Game::theGame->bounceLeft_++;
			GE161::Game::theGame->penalty = true;
		}
		bounce = true;
	}
	else if (right)
	{
		x_delta = -(rand() % 3 + 1);
		if (t)
		{
			GE161::Game::theGame->bounceRight_++;
		}
		bounce = true;
	}
	if (down)
	{
		y_delta = rand() % 3 + 1;
		bounce = true;
	}
	else if (up)
	{
		y_delta = -(rand() % 3 + 1);
		bounce = true;
	}
	return bounce;
}
// Paddle's movement
bool GE161::GameObject::BounceoffScreen()
{
	offScreen();
	bool bounce = false;
	if (down)
	{
		y_delta = 1;
		bounce = true;
	}
	else if (up)
	{
		y_delta = -1;
		bounce = true;
	}
	return bounce;
}

bool GE161::GameObject::offScreen()
{
	bool bounce = false;
	if (getY() + yFrame >= GE161::Game::theGame->window()->clientHeight())
	{
		up = true;
		bounce = true;
	}
	else
		up = false;
	if (getY() <= 0)
	{
		down = true;
		bounce = true;
	}
	else
		down = false;
	if (getX() + xFrame >= GE161::Game::theGame->window()->clientWidth())
	{
		right = true;
		bounce = true;
	}
	else
		right = false;
	if (getX() <= 0)
	{
		left = true;
		bounce = true;
	}
	else
		left = false;
	return bounce;
}


void GE161::GameObject::writeText()
{
	//if(sceneName)
	text = new Texty(GE161::Game::theGame->getRenderer(), GE161::Game::basePath() + "Aloha.ttf", 14, true);

	text->write("Hello! This is a Pong Game!", 100, 100);
	text->write("Have Fun!", Texty::NEXT_LINE);
	text->write("Left:" + std::to_string(GE161::Game::theGame->bounceLeft_), Texty::NEXT_LINE);
	text->write("  Right: " + std::to_string(GE161::Game::theGame->bounceRight_));
	text->write("Score: " + std::to_string(GE161::Game::theGame->score), Texty::NEXT_LINE);

	text->write("Life: " + std::to_string(GE161::Game::theGame->life), 500, 50);
	text->write("Gold: " + std::to_string(GE161::Game::theGame->coin), Texty::NEXT_LINE);

}

void GE161::GameObject::writeText(std::string content)
{
	//if(sceneName)
	text = new Texty(GE161::Game::theGame->getRenderer(), GE161::Game::basePath() + "Aloha.ttf", 14, true);
	text->write(content, 100, 100);
	text->write("", Texty::NEXT_LINE);

	SDL_RenderPresent(GE161::Game::theGame->getRenderer());
}

