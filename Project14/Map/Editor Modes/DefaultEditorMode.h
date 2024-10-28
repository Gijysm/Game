#ifndef DEFAULTMODE_H
#define DEFAULTMODE_H

#include "EditorMode.h"
#include "../../GUI/Gui.h"

class EditorMode;
class State;
class StateData;
class TileMap;
class Tile;
class GUI;

using gui::TextureSelector;

class DefaultEditorMode : public EditorMode
{
private:
    TextureSelector* Texture_sel;
    RectangleShape slidebar;
    RectangleShape SelectorRect;
    RectangleShape collisionbox;
    Text CursorText;
    IntRect Texture_rect;
    bool collision;
    bool TileAddLock;
    short type;
    int layer;

    void InitVariables();
    void InitGui();
    
public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* es_data);
    virtual ~DefaultEditorMode();
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderButton(RenderTarget& target);
    void renderGui(RenderTarget* target);
    void render(RenderTarget* target = NULL);
};
#endif