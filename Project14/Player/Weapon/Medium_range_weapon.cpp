#include "..//..//stdafx.h"
#include "Medium_range_weapon.h"

Medium_range_weapon::Medium_range_weapon(Texture& texture, Vector2f Position):Weapon(texture, Position)
{

}
Medium_range_weapon::~Medium_range_weapon()
{
}

void Medium_range_weapon::updatePosition(const float& dt, Vector2f Position)
{
    this->sprite.setPosition(Position);
}
void Medium_range_weapon::render(RenderTarget& target, Shader* shader, Vector2f Pos)
{
    if(shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", Pos);
        target.draw(this->sprite, shader);
    }
    else
        target.draw(this->sprite);
}