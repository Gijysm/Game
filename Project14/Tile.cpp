#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = 0;
	this->type = false;
}

Tile::Tile(unsigned x, unsigned y, float gridSizeF, const Texture& tex,
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

const string Tile::getAsString() const
{
	stringstream ss;

	ss << this->shape.getTextureRect().left << " " << 
		this->shape.getTextureRect().top << " " << this->collision <<
		" " << this->type;
	return ss.str();
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target)
{
	target.draw(this->shape);
}
