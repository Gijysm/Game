#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AtributeComponent.h"

class MovementComponent;
class HitboxComponent;
class AnimationComponent;
class AtributeComponent;
class Entity
{
private:

	void InitVariables();

protected:
	Sprite sprite;
	HitboxComponent* hitboxComponent;
	MovementComponent* Movecomponent;
	AnimationComponent* animationComponent;
	AtributeComponent* atributeComponent;
public:
	Entity();
	virtual ~Entity();

	virtual const Vector2f& getPosition() const;
	virtual const Vector2i getGridPos(const int Gridsize) const;
	virtual const FloatRect& getGlobalBounds() const;
	virtual void SetPosition(const float x, const float y);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	void CreateHitBoxComponent(Sprite& sprite,
		float off_set_x, float off_set_y,
		float width, float height);
	void CreateSprite(Texture& texture);
	const FloatRect& GetNextPosition(const float& dt) const;
	void CreateMovementComponent(const float MaxVelocity,
		const float& acceleration, const float& deceleration);
	void createAtributeComponent(const int level);
	void CreateAnimationComponent(map < string, Texture>& texture);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget& target) = 0;
};


#endif // !ENTITY_H
