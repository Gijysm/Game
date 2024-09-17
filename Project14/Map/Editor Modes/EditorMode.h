#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../../States/State.h"
#include "../../Map/TileMap.h"


class State;
class StateData;
class TileMap;
class Tile;

class EditorStateData
{
public:
    EditorStateData();
    virtual ~EditorStateData();
    
    bool Exit;
    bool paused;
    Font* font;
    View *view;
    map<string, int>* KeyBinds; 
    float *Keytime;
    float *KeytimeMax;

    Vector2i *MousePosScreen;
    Vector2i *MousePosWindow;
    Vector2f *MousePosView;
    Vector2i *MousePosGrid;
};

class EditorMode
{
private:
protected:
    EditorStateData* esData;
    StateData* state_data;
    TileMap* tile_map;
    Font* font;
    VideoMode vm;
public:
    EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* es_data);
    virtual ~EditorMode();
    
    void updatePmenuButton();

    const bool& GetQuit() const;
    const bool GetKeyTime();
    void EndState();
    void PausedState();
    void UnPausedState();

    // void UpdateEditorInput(const float& dt);
    // void renderPmenuButton(RenderTarget& target);
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void renderButton(RenderTarget& target) = 0;
    virtual void renderGui(RenderTarget* target) = 0;
    virtual void render(RenderTarget* target = NULL) = 0;
};
#endif