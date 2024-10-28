#include "..//../stdafx.h"
#include "EditorMode.h"
EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
: Statedata(state_data), Tile_map(tile_map),editor(editor_state_data)
{
    
}
const bool EditorMode::GetKeyTime()
{
    if (*this->editor->Keytime > *this->editor->KeytimeMax)
    {
        *this->editor->Keytime = 0;
        return true;
    }
    return false;
}
EditorMode::~EditorMode()
{
    
}