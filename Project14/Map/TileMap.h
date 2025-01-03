#ifndef TILEMAP_H
#define TILEMAP_H
#include "../Map/RegularTile.h"
#include "../Player/Entity.h"
#include "../Map/EnemySpawnerTile.h"
class  RegularTile;
class Tile;
class Entity;
class EnemySpawnerTile;
class TileMap
{
private:
	int layers;
	int GridsizeU;
	int GridSizeF;
	RectangleShape collisionbox;
	Vector2i MaxSizeWorldI;
	Vector2u maxGridSize_T;
	Vector2f MaxSizeWorldF;
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
	TileMap(const string& texture_file);
	virtual ~TileMap();

	const Texture* getTileSheet()const;

	const bool TileIsEmpty(const int x, const int y, const int z) const;
	const int getStackSize(const int x, const int y, const int layer) const;

	void AddTile(const int x, const int y,
		const int z, const IntRect& tex_rect,
		const bool& collision, const short& type);
	void AddTile(const int x, const int y,
	const int z, const IntRect& tex_rect,
	const int& enemy_type,const int& enemy_amount,
	const int& enemy_T_T_S,const int& enemy_M_D );
	void RemoveTile(const int x, const int y, const int z, const int type = -1);
	void updateTiles(Entity* entity, const float& dt);
	void updateTilesCollision(Entity* entity, const float& dt);
	void updateViewBindsCollision(Entity* entity, const float& dt);
	void update(Entity* entity, const float& dt);

	const Vector2i& GetMaxSizeGrid() const;
	const Vector2f& GetMaxSizeF() const;
	const bool checkType(const int x, const int y, const int z, const int type) const;

	void saveToFile(const string file_name);
	void loadFromFile(const string file_name);
	void renderDeferrent(RenderTarget& target, Shader* shader = NULL, const Vector2f PlayerPos = Vector2f());
	void render(RenderTarget& target,const Vector2i& GridPosition, Shader* shader = NULL,
		const Vector2f PlayerPos = Vector2f(), bool Visability = true);
};
#endif
