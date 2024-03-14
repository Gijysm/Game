#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:

	Event event;
	RenderWindow *window;
	StateData Statedata;
	GraphicsSettings GFXSettings;

	stack<State*> states;

	Clock Clockdt;
	float dt;
	float GridSize;

	map<string, int> supportedKey;

	void InitWindow();
	void InitVariabes();
	void InitStateData();
	void InitGraphicsSettings();
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