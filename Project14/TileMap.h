#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include "Entity.h"
class Tile;
class Entity;
class TileMap
{
private:
	int layers;
	int GridsizeU;
	int GridSizeF;
	RectangleShape collisionbox;
	Vector2i maxGridSize;
	Vector2u maxGridSize_T;
	Vector2f MaxSizeWorld;
	vector<vector<vector<vector<Tile*>>>> T_map;
	stack<Tile*> deferredRenderStack;
	Texture tileSheet;
	string Texture_file;

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	void clear();

public:
	TileMap(float gridSize, int sizex, int sizey, int width, int height, const string& texture_file);
	virtual ~TileMap();

	const Texture* getTileSheet()const;

	const int getStackSize(const int x, const int y, const int layer) const;

	void AddTile(const int x, const int y,
		const int z, const IntRect& tex_rect,
		const bool& collision, const short& type);
	void RemoveTile(const int x, const int y, const int z);
	void updateCollision(Entity* entity, const float& dt);

	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	void update();
	void renderDeferrent(RenderTarget& target);
	void render(RenderTarget& target,const Vector2i& GridPosition, bool Visability);
};
#endif
