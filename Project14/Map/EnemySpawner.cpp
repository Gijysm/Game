#include "..//stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int x, int y, float gridsize, const Texture& tex,
        const IntRect& tex_rect,int type,
    int amount,
    int time_To_Spawn, int max_Distance):Tile(x, y, gridsize, tex, tex_rect, false, TileTypes::ENEMYSPAWNER)
{
    this->shape.setSize(Vector2f(gridsize, gridsize));
    this->shape.setPosition(Vector2f(Grid_position));
    this->shape.setFillColor(Color::White);
    this->Grid_position = Grid_position;
    this->type = type;
    this->amount = amount;
    this->timeToSpawn = time_To_Spawn;
    this->maxDistance = max_Distance;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::update(const float& dt)
{
}
void EnemySpawner::render(RenderTarget& render)
{
    render.draw(shape);
}