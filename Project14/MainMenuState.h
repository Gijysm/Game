#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Button.h"
#include "GameState.h"

class MainMenuState : public State
{
private:
	RectangleShape BackGround;
	Texture BackGroundTexture;
	Font font;

	map<string,Button*> MainMenuState_Btn;
public:
	MainMenuState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~MainMenuState();

	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
	void EndState();
	void Update_Input(const float& dt);

	void updateButton();
	void renderButton(RenderTarget* target = NULL);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif // !MAINMENUSTATE_H