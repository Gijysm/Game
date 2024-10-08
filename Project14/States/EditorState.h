#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include <valarray>

#include "../States/State.h"
#include "../GUI/Gui.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../Map/Editor Modes/DefaultEditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class Tile;
class EditorMode;
class EditorStateData;
class DefaultEditorMode;

enum class EditorModes
{
 DEFAULT_MODE = 0, ENEMY_MODE	
};

class EditorState:public State
{
private:
	EditorStateData* _E_States_Data;
	
	View MainView;
	TileMap* Tilemap;
	Button* Hide_Button;
	bool hiden;
	PauseMenu* pmenu;
	Font font;
	float GridSize;
	RenderWindow* window;
	GraphicsSettings* GFXSettings;
	map<string, int> Key_Binds; 
	stack<State*>* states;
	

	float cam_speed;
	
	vector<EditorMode*> modes;
	map<string, gui::Button*> Buttons;
public:
	EditorState(StateData* state_data);
	virtual ~EditorState();
	void InitVariables();
	void InitView();
	void InitBackGround();
	void InitFont();
	void InitEditorStateData();
	void InitButtons();
	void InitKeyBinds();
	void InitPmenu();
	void InitTileMap();
	void InitGui();

	void InitModes();
	
	void updateInput(const float& dt);
	void KeyTime(const float& dt);
	void updatePmenuButton();
	void updateButton();
	void updateGui(const float& dt);
	void UpdateEditorInput(const float& dt);
	void renderPmenuButton(RenderTarget& target);
	void renderButton(RenderTarget& target);
	void renderGui(RenderTarget* target);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
