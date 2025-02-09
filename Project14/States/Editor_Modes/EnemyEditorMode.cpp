#include "..//..//stdafx.h"
#include "EnemyEditorMode.h"


void EnemyEditorMode::InitVariables()
{
                type = 0;
              amount = 1;
       time_to_spawn = 60;
    maxDistance = 1000;
}

void EnemyEditorMode::InitGui()
{
    this->CursorText.setFillColor(Color::White);
    this->CursorText.setFont(*this->editor->font);
    this->CursorText.setCharacterSize(15);
    this->CursorText.setPosition(this->editor->MousePosView->x, this->editor->MousePosView->y);

    this->slidebar.setSize(Vector2f(50, this->Statedata->GFXSettings->resolution.height));
    this->slidebar.setFillColor(Color(50, 50, 50, 100));
    this->slidebar.setOutlineColor(Color(200, 200, 200, 150));
    this->slidebar.setOutlineThickness(1.f);

    this->SelectorRect.setSize(Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
    this->SelectorRect.setFillColor(Color(255, 255, 255, 70));
    this->SelectorRect.setOutlineThickness(1);
    this->SelectorRect.setOutlineColor(Color::Green);
    // this->SelectorRect.setTexture(this->Tile_map->getTileSheet());
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
    /*const int x, const int y,
    const int z, const IntRect& tex_rect,
    const int& enemy_type,const int& enemy_amount,
    const int& enemy_T_T_S,const int& enemy_M_D*/
    if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
    {
        if (this->TileAddLock)
        {
            if (!this->slidebar.getGlobalBounds().contains(Vector2f(*this->editor->MousePosWindow)))
            {
                this->Tile_map->AddTile(this->editor->MousePosGrid->x,
                    this->editor->MousePosGrid->y,
                    0, this->Texture_rect,
                    this->type, this->amount,
                    this->time_to_spawn,
                    this->maxDistance);
            }
        }
    }
    if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime())
    {
        if (!this->slidebar.getGlobalBounds().contains(Vector2f(*this->editor->MousePosWindow)))
        {
            // if(this->Tile_map->checkType(this->editor->MousePosGrid->x, this->editor->MousePosGrid->y, 0))
            this->Tile_map->RemoveTile(this->editor->MousePosGrid->x,
                this->editor->MousePosGrid->y,
                0, TileTypes::ENEMYSPAWNER);
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TYPE_INC"))) && this->GetKeyTime())
    {
        ++this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TYPE_DEC"))) && this->GetKeyTime())
    {
        if(this->type > 0)
            --this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TOGGLE_TILE_LOCK"))) && this->GetKeyTime())
    {
        if (this->TileAddLock)
            TileAddLock = false;
        else
            TileAddLock = true;
    }
    bool isCtrl_pressed = (Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl));
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TYPE_UP"))) && this->GetKeyTime())
    {
        
        if(isCtrl_pressed)
        {
            this->type--;
        }
        else
        {
            this->type++;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("AMOUNT_UP"))) && this->GetKeyTime())
    {
        if(isCtrl_pressed)
        {
            this->amount--;
        }
        else
        {
            this->amount++;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TTS_UP"))) && this->GetKeyTime())
    {
        if(isCtrl_pressed)
        {
            this->time_to_spawn--;
        }
        else
        {
            this->time_to_spawn++;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("MD_UP"))) && this->GetKeyTime())
    {
        if(isCtrl_pressed)
        {
            this->maxDistance--;
        }
        else
        {
            this->maxDistance++;
        }
    }
}
void EnemyEditorMode::updateGui(const float& dt)
{
    this->SelectorRect.setPosition(this->editor->MousePosGrid->x * this->Statedata->GridSize, this->editor->MousePosGrid->y * this->Statedata->GridSize);
    this->CursorText.setPosition(*this->editor->MousePosView + Vector2f(15, 10));
    stringstream ss;
    ss 
        // << "\n" << 
               << "\n" << "Enemy type: "<< this->            type 
             << "\n" << "Enemy amount: "<< this->          amount 
            << "\n" << "Time to spawn: "<< this->   time_to_spawn 
        << "\n" << "Distance to spawn: "<< this->maxDistance;
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
    target->setView(*this->editor->view);
    target->draw(this->CursorText);
    target->draw(this->SelectorRect);
    target->setView(target->getDefaultView());
    target->draw(this->slidebar);
}
