#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
class EditorState:public State
{
private:
	
	PauseMenu* pmenu;
	TileMap Map; 
	Font font;

	map<string, gui::Button*> Buttons;
public:
	EditorState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~EditorState();
	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
	void InitPmenu();
	void updateInput(const float& dt);

	void KeyTime(const float& dt);
	void updatePmenuButton();
	void updateButton();
	void renderPmenuButton(RenderTarget& target);
	void renderButton(RenderTarget& target);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
