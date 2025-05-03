#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H
#include "../Map/Tile.h"


class Tile;

class EnemySpawnerTile: public Tile
{
private:
    RectangleShape shape;
    
    // Vector2f position;
    Vector2i Grid_position;
    int enemy_type_,
    enemy_amount,
    enemy_timeToSpawn;
    float ememy_maxDistance;
    bool spawned = false;
protected:
public:
    EnemySpawnerTile( int x, int y, float gridSizeF, const Texture& tex,
        const IntRect& tex_rect,int enemy_type,
    int amount,
    int time_To_Spawn, int max_Distance);
    virtual ~EnemySpawnerTile();
    const bool getSpawned()const;
    
    void setSpawned(const bool spawned);
    void spawn();
    void clear();
    
    virtual const string getAsString() const;
    void update(const float& dt);
    void render(RenderTarget& render);
};
#endif