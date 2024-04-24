#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = 0;
	this->type = false;
}

Tile::Tile(int x, int y, float gridSizeF, const Texture& tex,
	const IntRect& tex_rect, bool collision, short type)
{
	
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setTexture(&tex);
	this->shape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->shape.setTextureRect(tex_rect);
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

void Tile::render(RenderTarget& target)
{
	target.draw(this->shape);
}
