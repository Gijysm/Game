#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "Gui.h"
#include "EditorState.h"
#include "GameState.h"
#include "SettingsState.h"

class MainMenuState : public State
{
private:
	RectangleShape BackGround;
	Texture BackGroundTexture;
	Font font;

	map<string,gui::Button*> MainMenuState_Btn;

	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	void updateInput(const float& dt);
	void updateButton();
	void renderButton(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif // !MAINMENUSTATE_H