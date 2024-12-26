#ifndef ENEMY_H
#define ENEMY_H

#include "..//..//Player//Entity.h"
#include "..//..//Map/EnemySpawnerTile.h"

class Entity;
class EnemySpawnerTile;

// enum Direction
// {
//     Top = 0,
//     Right,
//     Bottom,
//     Left
// };

class Enemy:protected Entity
{
protected:
    // EnemySpawner& spawner;
    // Direction dir;
    bool Attacking;
    virtual void InitVariables();
    virtual void InitComponent();
protected:

public:
    //Accessors

    virtual void InitAnnimations();
	
    AtributeComponent* getAtributeComponent();
    Enemy();
    virtual Vector2f GetPosition() { return this->sprite.getPosition(); }
    // string directionToString(Direction dir);
    virtual virtual ~Enemy();
    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt, Vector2f& mouse_view_pos);
    virtual void update(const float& dt);
    virtual void render(RenderTarget& target, Shader* shader = NULL, const bool Show_col = true, const Vector2f Light_Position = Vector2f());
};
#endif