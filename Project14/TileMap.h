#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include "Entity.h"
class Tile;
class Entity;
class TileMap
{
private:
	unsigned layers;
	unsigned GridsizeU;
	float GridSizeF;
	RectangleShape collisionbox;
	Vector2u maxGridSize;
	Vector2u maxGridSize_T;
	Vector2f MaxSizeWorld;
	vector<vector<vector<Tile*>>> T_map;
	Texture tileSheet;
	string Texture_file;

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	void clear();

public:
	TileMap(float gridSize, unsigned sizex, unsigned sizey, unsigned width, unsigned height, const string& texture_file);
	virtual ~TileMap();

	const Texture* getTileSheet()const;

	void AddTile(const unsigned x, const unsigned y, 
		const unsigned z, const IntRect& tex_rect,
		const bool& collision, const short& type);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);
	void updateCollision(Entity* entity);

	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	void update();
	void render(RenderTarget& target, Entity* entity = NULL);
};
#endif
