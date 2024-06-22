#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"



class Entity;

class Player:public Entity
{
private:
	bool Attacking;
	void InitVariables();
	void InitComponent();
protected:

public:
	//Accessors
	AtributeComponent* getAtributeComponent();
	Player(float x, float y, map < string, Texture>& texture);
	Vector2f GetPosition() { return this->sprite.getPosition(); }
	virtual ~Player();
	void update(const float& dt);
	void render(RenderTarget& target);
};

#endif