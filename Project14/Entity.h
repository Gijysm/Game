#ifndef ENTITY_H
#define ENTITY_H

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

class Entity
{
private:

protected:

	RectangleShape Shape;
	float Movespeed;

public:
	Entity();
	virtual ~Entity();

	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(RenderTarget* target);
};


#endif // !ENTITY_H
