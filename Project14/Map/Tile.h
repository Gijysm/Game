#ifndef TILE_H
#define TILE_H
#include "..//stdafx.h"

enum TileTypes
{
	DEFAULT = 0, DAMAGING, DOODAD
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
	Tile(int x, int y, float gridSizeF, const Texture& tex,
		const IntRect& tex_rect, bool collision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	const int& GetType() const;
	const string getAsString() const;
	const bool& getCollision() const;
	const bool& OutOfRage(Vector2f& Pos) const;
	const FloatRect getGlobalBounds() const;
	const bool intersects(const FloatRect bounds) const;
	const Vector2f& getPosition() const;

	void update();
	void render(RenderTarget& target, Shader* shader = NULL, Vector2f PlayerPos = Vector2f());
};

#endif