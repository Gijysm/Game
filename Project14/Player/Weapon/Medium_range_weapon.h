#ifndef MEDIUM_RANGE_WEAPON_H
#define MEDIUM_RANGE_WEAPON_H
#include "Weapon.h"
class Medium_range_weapon :
    public Weapon
{
public:
    Medium_range_weapon(Texture& texture, Vector2f Position);
    ~Medium_range_weapon();
    void updatePosition(const float& dt, Vector2f Position);
    void render(RenderTarget& target, Shader* shader = NULL, Vector2f Pos = Vector2f());
};

#endif // !MEDIUM_RANGE_WEAPON_H