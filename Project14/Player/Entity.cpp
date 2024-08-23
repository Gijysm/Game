#include "..//stdafx.h"
#include "Entity.h"

void Entity::InitVariables()
{
	this->animationComponent = NULL;
	this->Movecomponent = NULL;
	this->hitboxComponent = NULL;
	this->animationComponent = NULL;
	this->skillComponent = NULL;
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
	delete this->atributeComponent;
	delete this->skillComponent;
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
}

const FloatRect& Entity::GetNextPosition(const float& dt) const
{
	if (this->hitboxComponent && this->Movecomponent)
	{
	return this->hitboxComponent->getNextPos(Movecomponent->GetVelocity() * dt);
	}
	return FloatRect();
}

void Entity::CreateWeapon(Texture texture)
{
	this->peak = new Peak(texture, Vector2f(this->getPosition().x + 10, this->getPosition().y));
}

void Entity::CreateSkillComponent()
{
	this->skillComponent = new SkillComponent();
}

void Entity::CreateMovementComponent(const float MaxVelocity,
	const float& acceleration, const float& deceleration)
{
	this->Movecomponent = new MovementComponent(this->sprite, MaxVelocity, acceleration, deceleration);
}

void Entity::createAtributeComponent(const int level)
{
	this->atributeComponent = new AtributeComponent(level);
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

const Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return 
			this->hitboxComponent->getPosition() + 
				Vector2f(
						this->hitboxComponent->getGlobalBounds().width / 2.f,
						this->hitboxComponent->getGlobalBounds().height / 2.f
				);
		return 
			this->sprite.getPosition() +
				Vector2f(
						 this->sprite.getGlobalBounds().width / 2.f,
						 this->sprite.getGlobalBounds().height / 2.f
				);
}


const Vector2i Entity::getGridPos(const int Gridsize) const
{
	if (this->hitboxComponent)
		return Vector2i(static_cast<int>(this->hitboxComponent->getPosition().x) / Gridsize,
			static_cast<int>(this->hitboxComponent->getPosition().y) / Gridsize);
	return Vector2i(static_cast<int>(this->sprite.getPosition().x) / Gridsize,
		static_cast<int>(this->sprite.getPosition().y) / Gridsize);
}

const FloatRect& Entity::getGlobalBounds() const
{
		return this->hitboxComponent->getGlobalBounds();
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if(this->Movecomponent)
	{
		this->Movecomponent->move(dir_x, dir_y,dt);
	}
	if (this->skillComponent)
	{
		this->skillComponent->gainExp(SKILLS::Endurance,1);
		cout << this->skillComponent->getSkillLevel(SKILLS::Endurance) << endl;
	}
}

void Entity::update(const float& dt, Vector2f& mouse_view_pos)
{
}

void Entity::render(RenderTarget& target, Shader* shader)
{
	target.draw(this->sprite);
}
