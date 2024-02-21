#include "Entity.h"

void Entity::InitVariables()
{
	this->Movecomponent = NULL;
}

Entity::Entity()
{
	this->InitVariables();

}

Entity::~Entity()
{
	delete this->Movecomponent;
}

void Entity::SetPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::CreateSprite(Texture& texture)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(2.5, 2.5);
}

void Entity::CreateMovementComponent(const float MaxVelocity,
	const float& acceleration, const float& deceleration)
{
	this->Movecomponent = new MovementComponent(this->sprite, MaxVelocity, acceleration, deceleration);
}

void Entity::CreateAnimationComponent(map < string, Texture>& texture)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if(this->Movecomponent)
	{
		this->Movecomponent->move(dir_x, dir_y,dt);
	}
}

void Entity::update(const float& dt)
{
	if (this->Movecomponent)
	{
		this->Movecomponent->update(dt);
	}
}

void Entity::render(RenderTarget* target)
{
	target->draw(this->sprite);
}
