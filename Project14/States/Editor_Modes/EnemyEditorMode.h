#ifndef ENEMYEDITORMODE_H
#define ENEMYEDITORMODE_H

#include "EditorMode.h"
#include "../../Map/EnemySpawner.h"
class State;
class StateData;
class EditorMode;
class Tile;
class TileMap;
class gui::TextureSelector;

class EnemyEditorMode : public EditorMode
{
public:
    EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data);
    virtual ~EnemyEditorMode();

    void InitVariables();
    void InitGui();
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void renderGui(RenderTarget* target);
    void update(const float& dt);
    void render(RenderTarget& target);
    
};
#endif