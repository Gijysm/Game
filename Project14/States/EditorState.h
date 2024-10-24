#ifndef EDITORSTATE_H
#define EDITORSTATE_H
#include "../States/State.h"
#include "../GUI/Gui.h"
#include "../GUI/PauseMenu.h"
#include "../Map/TileMap.h"
#include "../States/Editor_Modes/EditorMode.h"
#include "../Map/Editor Modes/EditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class EditorMode;

enum class EditorModes
{
 DEFAULT_MODE = 0, ENEMY
};

class EditorStateData
{
public:
	EditorStateData()
	{
		
	}
	~EditorStateData()
	{
		
	}
	float GridSize;
	RenderWindow* window;
	GraphicsSettings* GFXSettings;
	map<string, int>* supportedKey; 
	stack<State*>* states;

	float *Keytime;
	float *KeytimeMax;

	map<string, int>* Key_binds;
	
	Vector2i *MousePosScreen;
	Vector2i *MousePosWindow;
	Vector2f *MousePosView;
	Vector2i *MousePosGrid;
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
	void renderPmenuButton(RenderTarget& target);
	void renderButton(RenderTarget& target);
	void renderGui(RenderTarget* target);

	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};
#endif
