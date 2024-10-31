#include "EnemyEditorMode.h"

#include "DefaultEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
    : EditorMode(state_data,tile_map, editor_state_data)
{
}

EnemyEditorMode::~EnemyEditorMode()
{
}

void EnemyEditorMode::updateInput(const float& dt)
{
}
void EnemyEditorMode::updateGui(const float& dt)
{
}
void EnemyEditorMode::update(const float& dt)
{
}

void EnemyEditorMode::render(RenderTarget& target)
{
}

void EnemyEditorMode::renderGui(RenderTarget* target)
{
}
