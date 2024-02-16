#include "Entity.h"

Entity::Entity()
{
	this->Shape.setSize(Vector2f(50.f, 50.f));
	this->Shape.setFillColor(Color::Red);
	this->Movespeed = 4.f;
}

Entity::~Entity()
{
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	this->Shape.move(dir_x * dt * Movespeed, dir_y * dt * Movespeed);
}

void Entity::update(const float& dt)
{

}

void Entity::render(RenderTarget* target)
{
	target->draw(this->Shape);
}
