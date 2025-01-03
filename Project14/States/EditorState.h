#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "../States/State.h"
#include "../GUI/Gui.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../States/Editor_Modes/EditorModes_Class.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class EditorMode;
class EditorModes_Class;
class DefaultEditorMode;
class EnemyEditorMode;
class EditorStateData;


enum class EditorModes
{
 DEFAULT_EDITOR_MODE = 0, ENEMY_EDITOR_MODE
};

class EditorState:public State
{
private:
	EditorStateData editorStateData;
	
	View MainView;
	TileMap* Tilemap;
	Button* Hide_Button;
	bool hiden;
	PauseMenu* pmenu;
	Font font;
	int cam_speed;
	int activemode;
	
	map<string, gui::Button*> Buttons;

	vector<EditorMode*> EModes;

	void InitEditorStates();
	void InitVariables();
	void InitView();
	// void InitBackGround();
	void InitFont();
	void InitButtons();
	void InitKeyBinds();
	void InitPmenu();
	void InitTileMap();
	void InitGui();
	void InitModes();
public:
	EditorState(StateData* state_data);
	virtual ~EditorState();
	
	void updateInput(const float& dt);

	void KeyTime(const float& dt);
	void updatePmenuButton();
	void updateButton();
	void updateGui(const float& dt);
	void UpdateEditorInput(const float& dt);
	void UpdateModes(const float& dt);
	void renderPmenuButton(RenderTarget& target);
	void renderButton(RenderTarget& target);
	void renderGui(RenderTarget& target);
	void renderModes(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
