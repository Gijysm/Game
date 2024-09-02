#ifndef ENEMY_H
#define ENEMY_H

#include "..//Player//Entity.h"

class Entity;
// enum Direction
// {
//     Top = 0,
//     Right,
//     Bottom,
//     Left
// };

class Enemy:public Entity
{
private:

    // Direction dir;
    bool Attacking;
    void InitVariables();
    void InitComponent();
protected:

public:
    //Accessors

    void InitAnnimations();
	
    AtributeComponent* getAtributeComponent();
    Enemy(float x, float y, std::map<std::string, sf::Texture>& textures, sf::Texture texture = Texture());
    Vector2f GetPosition() { return this->sprite.getPosition(); }
    // string directionToString(Direction dir);
    virtual ~Enemy();
    void updateAnimation(const float& dt);
    void update(const float& dt, Vector2f& mouse_view_pos);
    void render(RenderTarget& target, Shader* shader = NULL);
};
#endif