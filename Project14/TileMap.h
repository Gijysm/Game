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
	vector<vector<vector<Tile*>>> T_map;
	Texture tileTextureSheet;

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void AddTile(const unsigned x, const unsigned y, const unsigned z);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);
	void update();
	void render(RenderTarget& target);
};
#endif
