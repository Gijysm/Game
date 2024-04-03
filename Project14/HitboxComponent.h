#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H
#include "stdafx.h"

class HitboxComponent
{
private:
	double Offset_x, Offset_y;
	Sprite& sprite;
	RectangleShape hitbox;
	FloatRect nextPosition;
public:
	HitboxComponent(Sprite& sprite, float off_set_x, float off_set_y,
		float width, float height);
	virtual ~HitboxComponent();

	const FloatRect& getNextPos(const Vector2f& velocity);
	const Vector2f& getPosition()const;
	const FloatRect& getGlobalBounds() const;
	void setPosition(const Vector2f& position);
	void setPosition(const float x, const float y);
	bool Intersect(const FloatRect& frect);
	void update();
	void render(RenderTarget& target);
};
#endif
