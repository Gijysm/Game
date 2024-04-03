#include "stdafx.h"
#include "Entity.h"

void Entity::InitVariables()
{
	this->animationComponent = NULL;
	this->Movecomponent = NULL;
	this->hitboxComponent = NULL;
}

Entity::Entity()
{
	this->InitVariables();
}

Entity::~Entity()
{
	delete this->Movecomponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Entity::SetPosition(const float x, const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);

}

void Entity::stopVelocity()
{
	if (this->Movecomponent)
	{
		this->Movecomponent->stopVelocity();
	}
}

void Entity::stopVelocityX()
{
	if (this->Movecomponent)
	{
		this->Movecomponent->stopVelocityX();
	}
}

void Entity::stopVelocityY()
{
	if (this->Movecomponent)
	{
		this->Movecomponent->stopVelocityY();
	}
}

void Entity::CreateHitBoxComponent(Sprite& sprite, float off_set_x, float off_set_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, off_set_x, off_set_y,
		width, height);
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

const Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	return this->sprite.getPosition();
}

const Vector2u Entity::getGridPos(const unsigned Gridsize) const
{
	if (this->hitboxComponent)
		return Vector2u(static_cast<unsigned>(this->hitboxComponent->getPosition().x) / Gridsize,
			static_cast<unsigned>(this->hitboxComponent->getPosition().y) / Gridsize);
	return Vector2u(static_cast<unsigned>(this->sprite.getPosition().x) / Gridsize,
		static_cast<unsigned>(this->sprite.getPosition().y) / Gridsize);
}

const FloatRect& Entity::getGlobalBounds() const
{
	if(this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
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
}

void Entity::render(RenderTarget& target)
{
	target.draw(this->sprite);
	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}
