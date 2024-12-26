#ifndef SPIDER_H
#define SPIDER_H

#include "Enemy.h"

class Spider:public Enemy
{
protected:
    void InitVariables();
    void InitComponent();
    void InitAnnimations();
public:
    Spider(/*EnemySpawner& spawner*/float x, float y, std::map<std::string, sf::Texture>& textures, sf::Texture texture = Texture());
    ~Spider();
    void updateAnimation(const float& dt);
    void update(const float& dt, Vector2f& mouse_view_pos);
    void update(const float& dt);
    void render(RenderTarget& target, Shader* shader = NULL, const bool Show_col = true, const Vector2f Light_Position = Vector2f());
};
#endif
