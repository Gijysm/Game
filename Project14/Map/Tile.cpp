#include "..//stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = 0;
	this->type = 0;
}

Tile::Tile(short type, int x, int y, float gridSizeF, const Texture& tex,
	const IntRect& tex_rect, const bool collision)
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
const bool& Tile::getCollision() const
{
	return this->collision;
}
const int& Tile::GetType() const
{
	return this->type;
}
void Tile::update()
{
}

void Tile::render(RenderTarget& target, Shader* shader, Vector2f PlayerPos)
{
}

const bool& Tile::OutOfRage(Vector2f& Pos) const
{
	return 0;
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


