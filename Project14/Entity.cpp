#include "Entity.h"

void Entity::InitVariables()
{
	this->Movecomponent = NULL;
	this->sprite = NULL;
}

Entity::Entity()
{
	this->InitVariables();

}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::SetPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::CreateSprite(Texture* texture)
{
	this->sprite = new Sprite(*texture);
	this->sprite->setScale(2.5, 2.5);
}

void Entity::CreateMovementComponent(const float MaxVelocity)
{
	this->Movecomponent = new MovementComponent(MaxVelocity);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if(this->sprite && this->Movecomponent)
	{
		this->Movecomponent->move(dir_x, dir_y);
		this->sprite->move(this->Movecomponent->GetVelocity() * dt);
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(RenderTarget* target)
{
	if(this->sprite)
	{
		target->draw(*this->sprite);
	}
}
