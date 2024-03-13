#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
class TileMap
{
private:
	unsigned layers;
	unsigned GridsizeU;
	float GridSizeF;
	Vector2u maxSize;
	vector<vector<vector<Tile>>> T_map;

public:
	TileMap();
	virtual ~TileMap();

	void update();
	void render(RenderTarget& target);
};
#endif
