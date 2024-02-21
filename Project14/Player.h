#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player:public Entity
{
private:
	void InitVariables();
	void InitComponent();
protected:

public:
	Player(float x, float y, map < string, Texture>& texture);
	virtual ~Player();
	void update(const float& dt);
};

#endif