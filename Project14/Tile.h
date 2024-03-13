#ifndef TILE_H
#define TILE_H
#include "stdafx.h"
class Tile
{
private:
protected:
	RectangleShape shape;
public:
	Tile();
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();
	void update();
	void render(RenderTarget& target);
};

#endif