#ifndef ENTITY_H
#define ENTITY_H

#include "..//Component/AnimationComponent.h"
#include "..//Component/MovementComponent.h"
#include "..//Component/HitboxComponent.h"
#include "..//Component/AtributeComponent.h"
#include "..//Component/SkillComponent.h"
#include "..//Player/Weapon/Peak.h"

class MovementComponent;
class HitboxComponent;
class AnimationComponent;
class AtributeComponent;
class SkillComponent;
class Entity
{
private:

	void InitVariables();

protected:
	Sprite sprite;
	Peak* peak;
	HitboxComponent* hitboxComponent;
	MovementComponent* Movecomponent;
	AnimationComponent* animationComponent;
	AtributeComponent* atributeComponent;
	SkillComponent* skillComponent;
public:
	Entity();
	virtual ~Entity();
	virtual const Vector2f& getPosition() const;
	virtual const Vector2f getCenter() const;
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
	Vector2f GetSize() { return this->hitboxComponent->GetSize(); };
	const FloatRect& GetNextPosition(const float& dt) const;
	void CreateWeapon(Texture texture);
	void CreateSkillComponent();
	void CreateMovementComponent(const float MaxVelocity,
								 const float& acceleration, const float& deceleration);
	void createAtributeComponent(const int level);
	void CreateAnimationComponent(map < string, Texture>& texture);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt, Vector2f& mouse_view_pos) = 0;
	virtual void render(RenderTarget& target, Shader* shader) = 0;
};


#endif // !ENTITY_H
