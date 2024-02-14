#ifndef GAME_H
#define GAME_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace sf;
using namespace std;


class Game
{
private:
	Event event;
	RenderWindow *window;

	Clock Clockdt;
	float dt;

	void InitWindow();
public:
	Game();
	virtual ~Game();
	void UpdateDt();
	void updateSFMLEvent();
	void update();
	void render();
	void run();
};


#endif