#include "EnemyEditorMode.h"

#include "DefaultEditorMode.h"

void EnemyEditorMode::InitVariables()
{
}

void EnemyEditorMode::InitGui()
{
    this->CursorText.setFillColor(Color::White);
    this->CursorText.setFont(*this->font);
    this->CursorText.setCharacterSize(15);
    this->CursorText.setPosition(this->editor->MousePosView->x, this->editor->MousePosView->y);

    this->slidebar.setSize(Vector2f(50, this->Statedata->GFXSettings->resolution.height));
    this->slidebar.setFillColor(Color(50, 50, 50, 100));
    this->slidebar.setOutlineColor(Color(200, 200, 200, 150));
    this->slidebar.setOutlineThickness(1.f);

    this->SelectorRect.setSize(Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
    this->SelectorRect.setFillColor(Color(255,255,255,150));
    this->SelectorRect.setOutlineThickness(1);
    this->SelectorRect.setOutlineColor(Color::Green);
    this->SelectorRect.setTexture(this->Tile_map->getTileSheet());
}

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
    : EditorMode(state_data,tile_map, editor_state_data)
{
    this->InitVariables();
    this->InitGui();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

void EnemyEditorMode::updateInput(const float& dt)
{
}
void EnemyEditorMode::updateGui(const float& dt)
{
    this->SelectorRect.setPosition(this->editor->MousePosGrid->x * this->Statedata->GridSize, this->editor->MousePosGrid->y * this->Statedata->GridSize);
    this->CursorText.setPosition(*this->editor->MousePosView + Vector2f(15, 10));
    stringstream ss;
    this->CursorText.setPosition(*this->editor->MousePosView + Vector2f(15, 10));
    // ss << 
    //     << "\n" << 
    //     << "\n" << "Collision: " <<
    //     << "\n" << "Type: " << 
    //     << "\n" << "Tiles: " << 
    //     << "\n" << "Tile_lock: " <<;
    this->CursorText.setCharacterSize(15);
    this->CursorText.setString(ss.str());
}
void EnemyEditorMode::update(const float& dt)
{
    this->updateInput(dt);
    this->updateGui(dt);
}

void EnemyEditorMode::render(RenderTarget& target)
{
    this->renderGui(&target);
}

void EnemyEditorMode::renderGui(RenderTarget* target)
{
    target->draw(this->CursorText);
    target->draw(this->slidebar);
}
