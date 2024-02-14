#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "GameState.h"

class Game
{
private:
	Event event;
	RenderWindow *window;

	stack<State*> states;

	Clock Clockdt;
	float dt;

	void InitWindow();
	void initStates();
public:
	Game();
	virtual ~Game();
	void EndApplication();

	void UpdateDt();
	void updateSFMLEvent();
	void update();
	void render();
	void run();
};


#endif