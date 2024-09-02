#include "..//..//stdafx.h"
#include "../Weapon/Peak.h"

Peak::Peak(Texture& texture, Vector2f Position):Medium_range_weapon(texture, Position)
{
}
Peak::~Peak()
{
}
void Peak::updatePosition(const float& dt,const Vector2f& MousePos, Vector2f Position)
{
#define PI 3.141592653589793
    Medium_range_weapon::updatePosition(dt, Position);
    float Dx = MousePos.x - this->sprite.getPosition().x,
    Dy = MousePos.y - this->sprite.getPosition().y;
    float deg = atan2(Dy, Dx) * 180.f / PI;
    this->sprite.setRotation(deg+ 90.f);
}

void Peak::updatePosition(const float& dt, Vector2f Position)
{
    Medium_range_weapon::updatePosition(dt, Position);
}

void Peak::render(RenderTarget& target, Shader* shader, Vector2f Pos)
{
    Medium_range_weapon::render(target, shader, Pos);
}

