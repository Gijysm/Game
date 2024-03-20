#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, const Texture& tex, const IntRect& tex_rect)
{
	
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setTexture(&tex);
	this->shape.setPosition(x, y);
	this->shape.setTextureRect(tex_rect);
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(RenderTarget& target)
{
	target.draw(this->shape);
}
