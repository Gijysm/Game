#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(Sprite& sprite, const float MaxVelocity,
	const float& acceleration, const float& deceleration)
	:sprite(sprite), MaxVelocity(MaxVelocity),
	acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::GetMaxVelocity() const
{
	return this->MaxVelocity;
}

const Vector2f& MovementComponent::GetVelocity() const
{
	return this->velocity;
}

void MovementComponent::stopVelocity()
{
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0.f;
}

const bool MovementComponent::GetStates(const short unsigned State) const
{
	switch (State)
	{
	case Movement_States::Idle:
		if (this->velocity.x == 0 && this->velocity.y == 0)
			return true;
		break;
	case Movement_States::Moving:
		if (this->velocity.x != 0 || this->velocity.y != 0)
			return true;
		break;
	case Movement_States::Moving_Left:
		if (this->velocity.x < 0)
			return true;
		break;
	case Movement_States::Moving_Right:
		if (this->velocity.x > 0)
			return true;
		break;
	case Movement_States::Moving_Up:
		if (this->velocity.y < 0)
			return true;
		break;
	case Movement_States::Moving_Down:
		if (this->velocity.y > 0)
			return true;
		break;
	}
	return false;
}


void MovementComponent::update(const float& dt)
{
	if (this->velocity.x > 0)
	{
		if (this->velocity.x > this->MaxVelocity)
			this->velocity.x = MaxVelocity;

		this->velocity.x -= deceleration;
		if (this->velocity.x < 0)
			this->velocity.x = 0;
	}
	else if (this->velocity.x < 0)
	{
		if (this->velocity.x < -this->MaxVelocity)
			this->velocity.x = -MaxVelocity;

		this->velocity.x += deceleration;
		if (this->velocity.x > 0)
			this->velocity.x = 0;
	}

	if (this->velocity.y > 0)
	{
		if (this->velocity.y > this->MaxVelocity)
			this->velocity.y = MaxVelocity;

		this->velocity.y -= deceleration;
		if (this->velocity.y < 0)
			this->velocity.y = 0;
	}
	else if (this->velocity.y < 0)
	{
		if (this->velocity.y < -this->MaxVelocity)
			this->velocity.y = -MaxVelocity;

		this->velocity.y += deceleration;
		if (this->velocity.y > 0)
			this->velocity.y = 0;
	}
	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	this->velocity.x += acceleration * dir_x;
	this->velocity.y += acceleration * dir_y;

}
