#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"

class Entity
{
private:

	void InitVariables();

protected:
	Sprite* sprite;
	MovementComponent* Movecomponent;

public:
	Entity();
	virtual ~Entity();

	virtual void SetPosition(const float x, const float y);
	void CreateSprite(Texture* texture);
	void CreateMovementComponent(const float MaxVelocity);
	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt);
	virtual void render(RenderTarget* target);
};


#endif // !ENTITY_H
