#ifndef DEFAULTEDITORMODE_H
#define DEFAULTEDITORMODE_H

#include "EditorMode.h"
class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;
class gui::TextureSelector;

class DefaultEditorMode : public EditorMode
{
private:
    TextureSelector* Texture_sel;
    RectangleShape slidebar;
    RectangleShape SelectorRect;
    RectangleShape collisionbox;
    Button* Hide_Button;
    bool hiden;
    string text;
    Text CursorText;
    IntRect Texture_rect;
    bool collision;
    bool TileAddLock;
    short type;
    int layer;

    void InitVariables();
    void InitGui();
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void renderGui(RenderTarget* target);
public:
    DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~DefaultEditorMode();
    
void update(const float& dt);
    
void render(RenderTarget& target);
};
#endif