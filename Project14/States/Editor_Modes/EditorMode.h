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

class EditorMode
{
private:
    
protected:
    StateData* Statedata;
    TileMap* Tile_map;
    Font* font;
    
public:
    EditorMode(StateData* state_data, TileMap* tile_map, Font* font);
    virtual ~EditorMode();

    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    
    virtual void renderGui(RenderTarget* target) = 0;
    virtual void render(RenderTarget* target = NULL) = 0;
};
#endif