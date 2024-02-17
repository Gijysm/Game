#include "MovementComponent.h"

MovementComponent::MovementComponent(const float MaxVelocity)
	:MaxVelocity(MaxVelocity)
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

void MovementComponent::move(const float dir_x, const float dir_y)
{
	this->velocity.x = MaxVelocity * dir_x;
	this->velocity.y = MaxVelocity * dir_y;
}
