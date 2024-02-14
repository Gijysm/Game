#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H
#include "GameState.h"

class MainMenuState : public State
{
private:
	RectangleShape BackGround;
public:
	MainMenuState(RenderWindow* window, map<string, int>* supportedKey);
	virtual ~MainMenuState();

	void InitKeyBinds();
	void EndState();
	void Update_Input(const float& dt);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif // !MAINMENUSTATE_H