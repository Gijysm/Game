#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	Event event;
	RenderWindow *window;

	stack<State*> states;

	Clock Clockdt;
	float dt;

	map<string, int> supportedKey;

	void InitWindow();
	void initStates();
	void InitKeys();
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