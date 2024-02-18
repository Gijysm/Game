#include "MovementComponent.h"

MovementComponent::MovementComponent(Sprite& sprite, const float MaxVelocity)
	:sprite(sprite), MaxVelocity(MaxVelocity)
{
}

MovementComponent::~MovementComponent()
{
}

const Vector2f& MovementComponent::GetVelocity() const
{
	return this->velocity;
}

void MovementComponent::update(const float& dt)
{

}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	this->velocity.x = MaxVelocity * dir_x;
	this->velocity.y = MaxVelocity * dir_y;

	this->sprite.move(this->velocity * dt);
}
