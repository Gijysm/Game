#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H
#include "stdafx.h"

class HitboxComponent
{
private:
	double Offset_x, Offset_y;
	Sprite& sprite;
	RectangleShape hitbox;
public:
	HitboxComponent(Sprite& sprite, float off_set_x, float off_set_y,
		float width, float height);
	virtual ~HitboxComponent();

	bool checkIntersect(const FloatRect& frect);
	void update();
	void render(RenderTarget& target);
};
#endif
