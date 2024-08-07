#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Entity;
enum Direction
{
	Top = 0,
	Right,
	Bottom,
	Left
};

class Player:public Entity
{
private:

	Direction dir;
	bool Attacking;
	void InitVariables();
	void InitComponent();
protected:

public:
	//Accessors

	AtributeComponent* getAtributeComponent();
	Player(float x, float y, map < string, Texture>& texture, Texture& Weapon);
	Vector2f GetPosition() { return this->sprite.getPosition(); }
	string directionToString(Direction dir);
	virtual ~Player();
	void update(const float& dt, Vector2f& mouse_view_pos);
	void render(RenderTarget& target, Shader* shader = NULL);
};

#endif