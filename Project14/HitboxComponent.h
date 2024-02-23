#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;

class HitboxComponent
{
private:
	double Offset_x, Offset_y;
	Sprite& sprite;
	RectangleShape hitbox;
public:
	HitboxComponent(Sprite& sprite, double off_set_x, double off_set_y,
		float width, float height);
	virtual ~HitboxComponent();

	bool checkIntersect(const FloatRect& frect);
	void update();
	void render(RenderTarget& target);
};
#endif
