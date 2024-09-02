#ifndef PEAK_H
#define PEAK_H
#include "Medium_range_weapon.h"
class Peak : public Medium_range_weapon
{
public:
	Peak(Texture& texture, Vector2f Position);
	~Peak();
	void updatePosition(const float& dt,const Vector2f& MousePos, Vector2f Position);
	void updatePosition(const float& dt, Vector2f Position);
	void render(RenderTarget& target, Shader* shader = NULL, Vector2f Pos = Vector2f());
};

#endif // !PEAK_H