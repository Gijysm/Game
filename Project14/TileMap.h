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
	string Texture_file;

public:
	TileMap(float gridSize, unsigned width, unsigned height, const string& texture_file);
	virtual ~TileMap();

	const Texture* getTileSheet()const;

	void AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect& tex_rect);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

	void saveToFile(const string file_name);
	void loadToFile(const string file_name);
	void update();
	void render(RenderTarget& target);
};
#endif
