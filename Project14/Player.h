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
	Player(float x, float y, Texture* texture);
	virtual ~Player();
};

#endif