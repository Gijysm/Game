#include "..//stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = 0;
	this->type = false;
}

Tile::Tile(int x, int y, float gridSizeF, const Texture& tex,
	const IntRect& tex_rect, bool collision, short type)
{
	this->shape.setTexture(tex);
	this->shape.setTextureRect(tex_rect);

	float scaleX = gridSizeF / static_cast<float>(tex_rect.width);
	float scaleY = gridSizeF / static_cast<float>(tex_rect.height);
	this->shape.setScale(scaleX, scaleY);

	this->shape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->collision = collision;
	this->type = type; 
}

Tile::~Tile()
{
}

const int& Tile::GetType() const
{
	return type;
}

const string Tile::getAsString() const
{
	stringstream ss;

	ss << this->shape.getTextureRect().left << " " << 
		this->shape.getTextureRect().top << " " << this->collision <<
		" " << this->type;
	return ss.str();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool Tile::intersects(const FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds) ;
}

const Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target, Shader* shader, Vector2f PlayerPos)
{
	if(shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", PlayerPos);
		target.draw(this->shape, shader);
	}
	else
		target.draw(this->shape);
}
