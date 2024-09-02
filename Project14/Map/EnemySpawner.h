#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H

class EnemySpawner
{
private:
    RectangleShape shape;
    
    // Vector2f position;
    Vector2i Grid_position;
    int type,
    amount,
    timeToSpawn;
    float maxDistance;
protected:
public:
    EnemySpawner(Vector2i Grid_position, float gridsize,int type,
    int amount,
    int time_To_Spawn, int max_Distance);
    virtual ~EnemySpawner();

    void spawn();
    void clear();

    void update(const float& dt);
    void render(RenderTarget& render);
};
#endif