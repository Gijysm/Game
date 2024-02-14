#ifndef GAME_H
#define GAME_H
#include "State.h"

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