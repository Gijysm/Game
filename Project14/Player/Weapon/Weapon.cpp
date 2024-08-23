#include "..//..//stdafx.h"
#include "../Player.h"

Weapon::Weapon(Texture& texture, Vector2f Position)
{
	this->texture = texture;
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(3, 3);
	this->sprite.setPosition(Position);
	this->sprite.setOrigin(
		this->sprite.getGlobalBounds().width / 5.f,
		this->sprite.getGlobalBounds().height / 2.f
	);
}

Weapon::~Weapon()
{
}

void Weapon::setPosition(const Vector2f& position)
{
	this->sprite.setPosition(position);
}

void Weapon::setRotation(const float& rotation)
{
	this->sprite.setRotation(rotation);
}

const Vector2f& Weapon::getPosition() const
{
	return this->sprite.getPosition();
}

void Weapon::updatePosition(const float& dt, Vector2f Position)
{
		this->sprite.setPosition(Position);
}

void Weapon::render(RenderTarget& target, Shader* shader, Vector2f Pos)
{
	if(shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", Pos);
		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);
}
