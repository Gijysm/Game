#include "..//../stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::InitVariables()
{
    this->layer = 0;
    this->Texture_rect = IntRect(0, 0, static_cast<int>(16), static_cast<int>(16));
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->TileAddLock = false;
    
}
DefaultEditorMode::~DefaultEditorMode()
{
    delete this->Texture_sel;
}

void DefaultEditorMode::InitGui()
{
    this->CursorText.setFillColor(Color::White);
    this->CursorText.setFont(*this->font);
    this->CursorText.setCharacterSize(15);
    this->CursorText.setPosition(this->MousePos.x, this->MousePos.y);
    this->slidebar.setSize(Vector2f(50, this->Statedata->GFXSettings->resolution.height));
    this->slidebar.setFillColor(Color(50, 50, 50, 100));
    this->slidebar.setOutlineColor(Color(200, 200, 200, 150));
    this->slidebar.setOutlineThickness(1.f);
    this->SelectorRect.setSize(Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
    this->SelectorRect.setFillColor(Color(255,255,255,150));
    this->SelectorRect.setOutlineThickness(1);
    this->SelectorRect.setOutlineColor(Color::Green);

    this->SelectorRect.setTexture(this->Tile_map->getTileSheet());

    this->Texture_sel = new gui::TextureSelector(16, 16, 400, 224, 16,
        this->Tile_map->getTileSheet(), this->font,
        "Hide_Tile", vm);
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, Font* font)
: EditorMode(state_data, tile_map, font)
{
    this->InitVariables();
    this->InitGui();
}

void DefaultEditorMode::updateInput(const float& dt)
{
    if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
    {
        if (!this->Texture_sel->GetActive() && !this->slidebar.getGlobalBounds().contains(Vector2f(this->MousePosWindow)))
        {
            if (this->TileAddLock)
            {
                if (this->Tile_map->TileIsEmpty(this->MousePosGrid.x, this->MousePosGrid.y, 0))
                {
                    this->Tile_map->AddTile(this->MousePosGrid.x, this->MousePosGrid.y, 0, this->Texture_rect, this->collision, this->type);
                }
            }
            else
            {
                this->Tile_map->AddTile(this->MousePosGrid.x, this->MousePosGrid.y, 0, this->Texture_rect, this->collision, this->type);
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
            this->Tile_map->RemoveTile(this->MousePosGrid.x, this->MousePosGrid.y, 0);
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))) && this->GetKeyTime())
    {
        if (!this->paused)
        {
            this->PausedState();
        }
        else
        {
            this->UnPausedState();
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("TOGGLE_COLLISION"))) && this->GetKeyTime())
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
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("TYPE_INC"))) && this->GetKeyTime())
    {
        ++this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("TYPE_DEC"))) && this->GetKeyTime())
    {
        if(this->type > 0)
            --this->type;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("TOGGLE_TILE_LOCK"))) && this->GetKeyTime())
    {
        if (this->TileAddLock)
            TileAddLock = false;
        else
            TileAddLock = true;
    }
}

void DefaultEditorMode::updateGui(const float& dt)
{
    this->Texture_sel->update(MousePosWindow, dt);
    if(!this->Texture_sel->GetActive())
    {
        this->SelectorRect.setPosition(this->MousePosGrid.x * this->Statedata->GridSize, this->MousePosGrid.y * this->Statedata->GridSize);
        this->SelectorRect.setTextureRect(this->Texture_rect);
    }
    stringstream ss;
    this->CursorText.setPosition(MousePosView + Vector2f(15, 10));
    ss << MousePosView.x << " " << MousePosView.y << "\n" << MousePosGrid.x << " " << MousePosGrid.y << "\n"
        << this->Texture_rect.left << " " << this->Texture_rect.width
        << "\n" << this->Texture_rect.top << " " << this->Texture_rect.height
        << "\n" << "Collision: " << this->collision << 
        "\n" << "Type: " << this->type
        << "\n" << "Tiles: " << this->Tile_map->getStackSize(this->MousePosGrid.x,
            this->MousePosGrid.y,
            this->layer)
        << "\n" << "Tile_lock: " << this->TileAddLock;
    this->CursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{
}

void DefaultEditorMode::renderGui(RenderTarget* target)
{
    if(!this->Texture_sel->GetActive())
    {
        target->setView(this->MainView);
        target->draw(this->SelectorRect);
    }
    target->setView(this->window->getDefaultView());
    this->Texture_sel->render(*target);
    target->draw(this->slidebar);

    target->setView(this->MainView);
    target->draw(this->CursorText);
}

void DefaultEditorMode::render(RenderTarget* target)
{
}
