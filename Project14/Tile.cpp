#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	
	this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(Color::Green);
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
