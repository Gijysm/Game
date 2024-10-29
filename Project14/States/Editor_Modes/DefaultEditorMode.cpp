#include "..//../stdafx.h"
#include "DefaultEditorMode.h"

void DefaultEditorMode::InitVariables()
{
    this->layer = 0;
    this->Texture_rect = IntRect(0, 0, static_cast<int>(16), static_cast<int>(16));
    this->collision = false;
    this->type = TileTypes::DEFAULT;
    this->TileAddLock = false;
    this->hiden = false;
    this->text = "Hide Button";
    
}
DefaultEditorMode::~DefaultEditorMode()
{
    delete this->Texture_sel;
    delete this->Hide_Button;
}

void DefaultEditorMode::InitGui()
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
    this->Hide_Button = new Button(gui::p2pX(85, *this->editor->vm), gui::p2pY(85, *this->editor->vm), gui::p2pX(12, *this->editor->vm), gui::p2pY(7, *this->editor->vm),
        this->font, text, gui::CharacterSize(*this->editor->vm), Color(100, 100, 200, 50),
        Color(50, 150, 200, 125),
        Color(30, 30, 70, 180), Color(100, 100, 200, 150),
        Color(50, 150, 200, 185),
        Color(30, 30, 70, 230));
    this->Texture_sel = new gui::TextureSelector(16, 16, 400, 224, 16,
        this->Tile_map->getTileSheet(), *this->font,
        "Hide_Tile", *this->editor->vm);
}

DefaultEditorMode::DefaultEditorMode(StateData* state_data, TileMap* tile_map, EditorStateData* editor_state_data)
: EditorMode(state_data, tile_map, editor_state_data)
{
    this->InitVariables();
    this->InitGui();
}

void DefaultEditorMode::updateInput(const float& dt)
{
    if (this->Hide_Button->isPressed() && this->GetKeyTime())
    {
        if(this->hiden)
        {
            this->hiden = false;
        }
        else
        {
            this->hiden = true;
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
    {
        if (!this->Texture_sel->GetActive() && !this->slidebar.getGlobalBounds().contains(Vector2f(*this->editor->MousePosWindow)))
        {
            if (this->TileAddLock)
            {
                if (this->Tile_map->TileIsEmpty(this->editor->MousePosGrid->x, this->editor->MousePosGrid->y, 0))
                {
                    this->Tile_map->AddTile(this->editor->MousePosGrid->x, this->editor->MousePosGrid->y, 0, this->Texture_rect, this->collision, this->type);
                }
            }
            else
            {
                this->Tile_map->AddTile(this->editor->MousePosGrid->x, this->editor->MousePosGrid->y, 0, this->Texture_rect, this->collision, this->type);
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
            this->Tile_map->RemoveTile(this->editor->MousePosGrid->x, this->editor->MousePosGrid->y, 0);
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->editor->Key_binds->at("TOGGLE_COLLISION"))) && this->GetKeyTime())
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
    this->Hide_Button->update(*this->editor->MousePosWindow);
}

void DefaultEditorMode::updateGui(const float& dt)
{
    this->Texture_sel->update(*this->editor->MousePosWindow, dt, hiden);
    if(!this->Texture_sel->GetActive())
    {
        this->SelectorRect.setPosition(this->editor->MousePosGrid->x * this->Statedata->GridSize, this->editor->MousePosGrid->y * this->Statedata->GridSize);
        this->SelectorRect.setTextureRect(this->Texture_rect);
    }
    stringstream ss;
    this->CursorText.setPosition(*this->editor->MousePosView + Vector2f(15, 10));
    ss << this->editor->MousePosView->x << " " << this->editor->MousePosView->y << "\n" << this->editor->MousePosGrid->x << " " << this->editor->MousePosGrid->y << "\n"
        << this->Texture_rect.left << " " << this->Texture_rect.width
        << "\n" << this->Texture_rect.top << " " << this->Texture_rect.height
        << "\n" << "Collision: " << this->collision << 
        "\n" << "Type: " << this->type
        << "\n" << "Tiles: " << this->Tile_map->getStackSize(this->editor->MousePosGrid->x,
            this->editor->MousePosGrid->y,
            this->layer)
        << "\n" << "Tile_lock: " << this->TileAddLock;
    this->CursorText.setCharacterSize(15);
    this->CursorText.setString(ss.str());
}

void DefaultEditorMode::update(const float& dt)
{
    updateInput(dt);
    updateGui(dt);
}

void DefaultEditorMode::renderGui(RenderTarget* target)
{
    
    if(!this->Texture_sel->GetActive())
    {
        target->setView(*this->editor->view);
        target->draw(this->SelectorRect);
    }
    target->setView(this->Statedata->window->getDefaultView());
    this->Hide_Button->render(*target);
    this->Texture_sel->render(*target, hiden);
    target->draw(this->slidebar);

    target->setView(*this->editor->view);
    target->draw(this->CursorText);
}

void DefaultEditorMode::render(RenderTarget& target)
{
    renderGui(&target);
}
