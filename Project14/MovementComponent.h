#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>

using namespace sf;
using namespace std;

class MovementComponent
{
private:
	Sprite& sprite;

	float MaxVelocity;

	Vector2f velocity;
	Vector2f acceleration;
	Vector2f deceleration;
protected:

public:

	MovementComponent(Sprite& sprite, const float MaxVelocity);
	virtual ~MovementComponent();

	const Vector2f& GetVelocity() const;

	void update(const float& dt);
	void move(const float dir_x, const float dir_y, const float& dt);
};
#endif
