#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;
class EditorState:public State
{
private:
	TileMap* Tilemap;
	PauseMenu* pmenu;
	RectangleShape SelectorRect;
	Font font;

	map<string, gui::Button*> Buttons;
public:
	EditorState(StateData* state_data);
	virtual ~EditorState();
	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
	void InitPmenu();
	void InitTileMap();
	void InitGui();
	void updateInput(const float& dt);

	void KeyTime(const float& dt);
	void updatePmenuButton();
	void updateButton();
	void updateGui();
	void renderPmenuButton(RenderTarget& target);
	void renderButton(RenderTarget& target);
	void renderGui(RenderTarget* target);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
