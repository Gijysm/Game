#ifndef PEAK_H
#define PEAK_H
#include "Medium_range_weapon.h"
class Peak : public Medium_range_weapon
{
public:
	Peak(Texture& texture, Vector2f Position);
	~Peak();
};

#endif // !PEAK_H