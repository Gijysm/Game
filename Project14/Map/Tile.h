#ifndef TILE_H
#define TILE_H
#include "..//stdafx.h"

enum TileTypes
{
	DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER
};

class Tile
{
private:
protected:
	Sprite shape;
	short type;  
	bool collision;
public:
	Tile();
	Tile(short type , int x, int y, float gridSizeF, const Texture& tex,
		const IntRect& tex_rect, const bool collision = false);
	virtual ~Tile();

	virtual const int& GetType() const;
	virtual const string getAsString() const = 0;
	virtual const bool& OutOfRage(Vector2f& Pos) const;
	virtual const FloatRect getGlobalBounds() const;
	virtual const bool intersects(const FloatRect bounds) const;
	virtual const Vector2f& getPosition() const;
	virtual const bool& getCollision() const;
	virtual void update();
	virtual void render(RenderTarget& target, Shader* shader = NULL, Vector2f PlayerPos = Vector2f());
};

#endif