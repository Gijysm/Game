#include "stdafx.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(Sprite& sprite,
	float off_set_x, float off_set_y,
	float width, float height)
	: sprite(sprite), Offset_x(off_set_x),
	Offset_y(off_set_y)
{
	this->nextPosition.left = 0;
	this->nextPosition.top = 0;
	this->nextPosition.width = width;
	this->nextPosition.height = height;
	this->hitbox.setPosition(this->sprite.getPosition().x + off_set_x,
		this->sprite.getPosition().y + off_set_y);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(Color::Green);

}

HitboxComponent::~HitboxComponent()
{
}

const FloatRect& HitboxComponent::getNextPos(const Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;
	return this->nextPosition;
}

const Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const FloatRect& HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds(); 
}

void HitboxComponent::setPosition(const Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - Offset_x,
		position.y - Offset_y);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - Offset_x,
		y - Offset_y);
}

bool HitboxComponent::Intersect(const FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + Offset_x,
		this->sprite.getPosition().y + Offset_y);
}

void HitboxComponent::render(RenderTarget& target)
{
	target.draw(this->hitbox);
}
