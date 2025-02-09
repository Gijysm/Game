#include "..//stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int x, int y, float gridsize, const Texture& tex,
    const IntRect& tex_rect, int enemy_type,
    int amount, int time_To_Spawn, int max_Distance)
    : Tile(TileTypes::ENEMYSPAWNER, x, y, gridsize, tex, tex_rect, false)
{
    this->shape.setSize(Vector2f(gridsize, gridsize));
    this->shape.setPosition(Vector2f(Grid_position));
    this->shape.setFillColor(Color::White);
    this->Grid_position = Grid_position;
    this->enemy_type_ = enemy_type;
    this->enemy_amount = amount;
    this->enemy_timeToSpawn = time_To_Spawn;
    this->ememy_maxDistance = max_Distance;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

void EnemySpawnerTile::spawn()
{
}

const string EnemySpawnerTile::getAsString() const
{
    stringstream ss;

    ss << this->type << " " << this->shape.getTextureRect().left << " "
        << this->shape.getTextureRect().top << " " << this->enemy_type_ << " "
        << this->enemy_amount << " " << this->enemy_timeToSpawn << " "
        << this->ememy_maxDistance;
    cout << ss.str() << endl;
    return ss.str();
}

void EnemySpawnerTile::update(const float& dt)
{
}

void EnemySpawnerTile::render(RenderTarget& render)
{
    render.draw(shape);
}