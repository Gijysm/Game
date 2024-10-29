#ifndef PLAYER_H
#define PLAYER_H

#include "..//Player//Entity.h"

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

	void InitAnnimations();
	
	AtributeComponent* getAtributeComponent();
	Player(float x, float y, std::map<std::string, sf::Texture>& textures, sf::Texture& texture);
	Vector2f GetPosition() { return this->sprite.getPosition(); }
	string directionToString(Direction dir);
	virtual ~Player();
	void updateAnimation(const float& dt);
	void update(const float& dt, Vector2f& mouse_view_pos);
	void render(RenderTarget& target, Shader* shader = NULL, const bool showCol = true, const Vector2f Light_Position = Vector2f());
};

#endif