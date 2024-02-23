#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite,
	double off_set_x, double off_set_y,
	float width, float height)
	: sprite(sprite), Offset_x(off_set_x),
	Offset_y(off_set_y)
{
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

bool HitboxComponent::checkIntersect(const FloatRect& frect)
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
