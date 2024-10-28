#ifndef EDITORMODE_H
#define EDITORMODE_H
#include "../State.h"
#include "../../Map/TileMap.h"
#include "..//..//GUI/Gui.h"

class State;
class StateData;
class Tile;
class TileMap;

using namespace gui;

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

    View* view;
    VideoMode* vm;
	
    float *Keytime;
    float *KeytimeMax;

    Font* font;
    
    map<string, int>* Key_binds;
	
    Vector2i *MousePosScreen;
    Vector2i *MousePosWindow;
    Vector2f *MousePosView;
    Vector2i *MousePosGrid;
};

class EditorMode
{
private:
    
protected:
    EditorStateData* editor;
    StateData* Statedata;
    TileMap* Tile_map;
    Font* font;
    
public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EditorMode();

    const bool GetKeyTime();
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    
    virtual void renderGui(RenderTarget* target) = 0;
    virtual void render(RenderTarget* target = NULL) = 0;
};
#endif