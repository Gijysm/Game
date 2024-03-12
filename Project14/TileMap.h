#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
class TileMap
{
private:
	unsigned layers;
	unsigned GridsizeU;
	Vector2u maxSize;
	vector<vector<vector<Tile>>> T_map;

public:
	TileMap();
	virtual ~TileMap();
};
#endif
