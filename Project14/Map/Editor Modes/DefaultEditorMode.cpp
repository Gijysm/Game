#include "..//..//stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::InitVariables()
{
    this->layer = 0;
    this->Texture_rect = IntRect(0, 0, static_cast<int>(16), static_cast<int>(16));
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->TileAddLock = false;
}

void DefaultEditorMode::InitGui()
{
    this->CursorText.setFillColor(Color::White);
    this->CursorText.setFont(*this->font);
    this->CursorText.setCharacterSize(15);
    
    this->slidebar.setSize(Vector2f(50, this->state_data->GFXSettings->resolution.height));
    this->slidebar.setFillColor(Color(50, 50, 50, 100));
    this->slidebar.setOutlineColor(Color(200, 200, 200, 150));
    this->slidebar.setOutlineThickness(1.f);
    this->SelectorRect.setSize(Vector2f(this->state_data->GridSize, this->state_data->GridSize));
    this->SelectorRect.setFillColor(Color(255,255,255,150));
    this->SelectorRect.setOutlineThickness(1);
    this->SelectorRect.setOutlineColor(Color::Green);

    this->SelectorRect.setTexture(this->tile_map->getTileSheet());

    this->Texture_sel = new gui::TextureSelector(16, 16, 400, 224, 16,
        this->tile_map->getTileSheet(), *this->font,
        "Hide_Tile", this->vm);
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* es_data) : EditorMode(state_data, tile_map, es_data)
{
    this->InitVariables();
    this->InitGui();
}
DefaultEditorMode::~DefaultEditorMode()
{
    delete this->Texture_sel;
}

void DefaultEditorMode::updateInput(const float& dt)
{
    if (Keyboard::isKeyPressed(Keyboard::Key(this->esData->KeyBinds->at("Close"))) && this->GetKeyTime())
    {
        if (!this->esData->paused)
        {
            this->PausedState();
        }
        else
        {
            this->UnPausedState();
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->esData->KeyBinds->at("TOGGLE_COLLISION"))) && this->GetKeyTime())
    {
        if (this->collision)
        {
            this->collision = false;
        }
        else
        {
            this->collision = true;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->esData->KeyBinds->at("TYPE_INC"))) && this->GetKeyTime())
    {
        ++this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->esData->KeyBinds->at("TYPE_DEC"))) && this->GetKeyTime())
    {
        if(this->type > 0)
            --this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->esData->KeyBinds->at("TOGGLE_TILE_LOCK"))) && this->GetKeyTime())
    {
        if (this->TileAddLock)
            TileAddLock = false;
        else
            TileAddLock = true;
    }
    if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
    {
        if (!this->Texture_sel->GetActive() && !this->slidebar.getGlobalBounds().contains(Vector2f(*this->esData->MousePosWindow)))
        {
            if (this->TileAddLock)
            {
                if (this->tile_map->TileIsEmpty(this->esData->MousePosGrid->x, this->esData->MousePosGrid->y, 0))
                {
                    this->tile_map->AddTile(this->esData->MousePosGrid->x, this->esData->MousePosGrid->y, 0, this->Texture_rect, this->collision, this->type);
                }
            }
            else
            {
                this->tile_map->AddTile(this->esData->MousePosGrid->x, this->esData->MousePosGrid->y, 0, this->Texture_rect, this->collision, this->type);
            }
        }
        else
        {
            this->Texture_rect = this->Texture_sel->getTextureRect();
        }
    }
    if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime())
    {
        if (!this->Texture_sel->GetActive())
        {
            this->tile_map->RemoveTile(this->esData->MousePosGrid->x, this->esData->MousePosGrid->y, 0);
        }
    }
}

void DefaultEditorMode::updateGui(const float& dt)
{
    this->Texture_sel->update(*this->esData->MousePosWindow, dt);
    if(!this->Texture_sel->GetActive())
    {
        this->SelectorRect.setPosition(this->esData->MousePosGrid->x * this->state_data->GridSize, this->esData->MousePosGrid->y * this->state_data->GridSize);
        this->SelectorRect.setTextureRect(this->Texture_rect);
    }
    stringstream ss;
    this->CursorText.setPosition(*this->esData->MousePosView + Vector2f(15, 10));
    ss << this->esData->MousePosGrid->x << " " << this->esData->MousePosGrid->y << "\n" <<this->esData->MousePosGrid->x << " " << this->esData->MousePosGrid->y << "\n"
        << this->Texture_rect.left << " " << this->Texture_rect.width
        << "\n" << this->Texture_rect.top << " " << this->Texture_rect.height
        << "\n" << "Collision: " << this->collision << 
        "\n" << "Type: " << this->type
        << "\n" << "Tiles: " << this->tile_map->getStackSize(this->esData->MousePosGrid->x,
            this->esData->MousePosGrid->y,
            this->layer)
        << "\n" << "Tile_lock: " << this->TileAddLock;
    this->CursorText.setString(ss.str());
}
void DefaultEditorMode::update(const float& dt)
{
    this->UpdateMousePosition(*this->esData->view);
    this->UpdateKeyTime(dt);
    this->updateInput(dt);
    if (!this->paused)
    {
        this->KeyTime(dt);
        this->updateInput(dt);
        this->updateGui(dt);
    }
    else
    {
        this->pmenu->update(*this->esData->MousePosWindow);
        this->updatePmenuButton();
    }
    //cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
}

void DefaultEditorMode::renderButton(RenderTarget& target)
{
}
void DefaultEditorMode::renderGui(RenderTarget* target)
{
    if(!this->Texture_sel->GetActive())
    {
        target->setView(*this->esData->view);
        target->draw(this->SelectorRect);
    }
    target->setView(this->state_data->window->getDefaultView());
    this->Texture_sel->render(*target);
    target->draw(this->slidebar);

    target->setView(*this->esData->view);
    target->draw(this->CursorText);
}

void DefaultEditorMode::render(RenderTarget* target)
{
}
