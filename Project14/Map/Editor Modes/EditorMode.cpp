#include "..//..//stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* es_data)
    : state_data(state_data), tile_map(tile_map), esData(es_data)
{
}

EditorMode::~EditorMode()
{
}

const bool& EditorMode::GetQuit() const
{
    return this->esData->Exit;
}

const bool EditorMode::GetKeyTime()
{
    if (this->esData->Keytime > this->esData->KeytimeMax)
    {
        this->esData->Keytime = 0;
        return true;
    }
    return false;
}
void EditorMode::EndState()
{
    this->esData->Exit = true;
}

void EditorMode::PausedState()
{
    this->esData->paused = true;
}

void EditorMode::UnPausedState()
{
   this->esData->paused = false;
}
