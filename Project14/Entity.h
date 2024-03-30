#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
class Entity
{
private:

	void InitVariables();

protected:
	Sprite sprite;
	HitboxComponent* hitboxComponent;
	MovementComponent* Movecomponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	virtual void SetPosition(const float x, const float y);
	void CreateHitBoxComponent(Sprite& sprite,
		float off_set_x, float off_set_y,
		float width, float height);
	void CreateSprite(Texture& texture);
	void CreateMovementComponent(const float MaxVelocity,
		const float& acceleration, const float& deceleration);
	void CreateAnimationComponent(map < string, Texture>& texture);
	virtual const Vector2f& getPosition() const;
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(RenderTarget& target);
};


#endif // !ENTITY_H
