#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "../../Map/EnemySpawnerTile.h"
class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;
class EnemySpawnerTile;
class gui::TextureSelector;

class EnemyEditorMode : public EditorMode
{
private:
    // TextureSelector* Texture_sel;
    RectangleShape slidebar;
    RectangleShape SelectorRect;
    IntRect Texture_rect;
    Text CursorText;
    bool TileAddLock = false;
    int type,
        amount,
        time_to_spawn;
        float maxDistance;
    // string text;
    // bool collision;
    // short type;
    // int layer;

    void InitVariables();
    void InitGui();
public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();
    
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void renderGui(RenderTarget* target);
    void update(const float& dt);
    void render(RenderTarget& target);
    
};
#endif