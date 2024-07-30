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
	Player(float x, float y, map < string, Texture>& texture);
	Vector2f GetPosition() { return this->sprite.getPosition(); }
	void loseHP(const int hp);
	void gainHP(const int hp);
	string directionToString(Direction dir);
	void loseEXP(const int exp);
	void gainEXP(const int exp);
	virtual ~Player();
	void update(const float& dt);
	void render(RenderTarget& target);
};

#endif