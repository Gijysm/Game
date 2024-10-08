#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H
#include "..//stdafx.h"

enum Movement_States {
	Idle = 0,
	Moving,
	Moving_Left,
	Moving_Right,
	Moving_Up,
	Moving_Down
};

class MovementComponent
{
private:
	Sprite& sprite;

	float MaxVelocity;

	Vector2f velocity;
	float acceleration;
	float deceleration;
protected:

public:

	MovementComponent(Sprite& sprite, const float MaxVelocity,
		const float& acceleration, const float& deceleration);
	virtual ~MovementComponent();

	const float& GetMaxVelocity() const;
	const Vector2f& GetVelocity() const;

	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	const bool GetStates(const short unsigned State) const;

	void update(const float& dt);
	void move(const float dir_x, const float dir_y, const float& dt);
};
#endif
