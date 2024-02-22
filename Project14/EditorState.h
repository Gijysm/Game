#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "State.h"
#include "Button.h"
class EditorState:public State
{
private:
	RectangleShape BackGround;
	Texture BackGroundTexture;
	Font font;

	map<string, Button*> MainMenuState_Btn;
public:
	EditorState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~EditorState();

	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
	void Update_Input(const float& dt);

	void updateButton();
	void renderButton(RenderTarget* target = NULL);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
