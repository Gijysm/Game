#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF, Texture& tex)
{
	
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setTexture(&tex);
	this->shape.setPosition(x, y);
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
