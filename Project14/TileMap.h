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
	Texture tileSheet;

public:
	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	const Texture* getTileSheet()const;

	void AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect& tex_rect);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);
	void update();
	void render(RenderTarget& target);
};
#endif
