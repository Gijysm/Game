#include "..//stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(Vector2i Grid_position, float gridsize, int type, int amount, int time_To_Spawn, int max_Distance)
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