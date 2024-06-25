#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->InitVariables();
	this->InitBackGround();
	this->InitView();
	this->InitFont();
	this->InitText();
	this->InitKeyBinds();
	this->InitButtons();
	this->InitPmenu();
	this->InitTileMap();
	this->InitGui();
}

EditorState::~EditorState()
{
	delete this->pmenu; 
	delete this->Tilemap;
	delete this->Texture_sel;
}


void EditorState::InitVariables()
{
	this->layer = 0;
	this->paused = false;
	this->Texture_rect = IntRect(0, 0, static_cast<int>(16), static_cast<int>(16));
	this->collision = false;
	this->type = TileTypes::DEFAULT;
}

void EditorState::InitView()
{
	this->MainView.setSize(Vector2f(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
	this->MainView.setCenter(this->Statedata->GFXSettings->resolution.width / 2.f,
		this->Statedata->GFXSettings->resolution.height/ 2.f);
}

void EditorState::InitBackGround()
{

}

void EditorState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void EditorState::InitButtons()
{
}



void EditorState::InitKeyBinds()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\EditorKey_binds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string Key2 = "";

		while (ifs >> key >> Key2)
		{
			this->KeyBinds[key] = this->supportedKey->at(Key2);
		}
	}
	else
	{
		throw "Error";
	}
	ifs.close();
}

void EditorState::InitPmenu()
{
	vm = this->Statedata->GFXSettings->resolution;
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->AddButtons("RESUME", gui::p2pY(33, vm), "Resume");
	this->pmenu->AddButtons("SAVE", gui::p2pY(46, vm), "SAVE");
	this->pmenu->AddButtons("LOAD", gui::p2pY(60, vm), "Load");
	this->pmenu->AddButtons("QUIT", gui::p2pY(74, vm), "Quit");
}

void EditorState::InitTileMap()
{
	this->Tilemap = new TileMap(this->Statedata->GridSize,16,16, 40, 40, "C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Grass\\GRASS.png");
}

void EditorState::InitGui()
{
	this->slidebar.setSize(Vector2f(50, this->Statedata->GFXSettings->resolution.height));
	this->slidebar.setFillColor(Color(50, 50, 50, 100));
	this->slidebar.setOutlineColor(Color(200, 200, 200, 150));
	this->slidebar.setOutlineThickness(1.f);
	this->SelectorRect.setSize(Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
	this->SelectorRect.setFillColor(Color(255,255,255,150));
	this->SelectorRect.setOutlineThickness(1);
	this->SelectorRect.setOutlineColor(Color::Green);

	this->SelectorRect.setTexture(this->Tilemap->getTileSheet());

	this->Texture_sel = new gui::TextureSelector(16, 16, 400, 224, 16,
		this->Tilemap->getTileSheet(), this->font,
		"Hide_Tile");
}

void EditorState::InitText()
{
	this->CursorText.setFillColor(Color::White);
	this->CursorText.setFont(font);
	this->CursorText.setCharacterSize(15);
}


void EditorState::updateInput(const float& dt)
{
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
}
void EditorState::KeyTime(const float& dt)
{
	int cam_speed = 100;
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->MainView.move(-cam_speed * dt, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->MainView.move(cam_speed * dt, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_UP"))))
	{
		this->MainView.move(0,-cam_speed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->MainView.move(0, cam_speed * dt);
	}

}

void EditorState::updatePmenuButton()
{
	if (this->pmenu->isButtonPressed("RESUME"))
	{
		this->UnPausedState();
	}
	if (this->pmenu->isButtonPressed("SAVE"))
	{
		this->Tilemap->saveToFile("Puk.txt");
	}
	if (this->pmenu->isButtonPressed("LOAD"))
	{
		this->Tilemap->loadFromFile("Puk.txt");
	}
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->EndState();
	}
}

void EditorState::updateButton()
{
}

void EditorState::updateGui(const float& dt)
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
		<< "\n" << "Tiles: " << this->Tilemap->getStackSize(this->MousePosGrid.x, this->MousePosGrid.y, this->layer);
	this->CursorText.setString(ss.str());
}

void EditorState::UpdateEditorInput(const float& dt)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
	{
		if (!this->Texture_sel->GetActive() && !this->slidebar.getGlobalBounds().contains(Vector2f(this->MousePosWindow)))
		{
		this->Tilemap->AddTile(this->MousePosGrid.x, this->MousePosGrid.y, 0, this->Texture_rect, this->collision, this->type);
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
			this->Tilemap->RemoveTile(this->MousePosGrid.x, this->MousePosGrid.y, 0);
		}
	}
}

void EditorState::renderPmenuButton(RenderTarget& target)
{
	this->pmenu->render(target);
}

void EditorState::renderButton(RenderTarget& target)
{
}

void EditorState::renderGui(RenderTarget* target)
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

void EditorState::update(const float& dt)
{
	this->UpdateMousePosition(&this->MainView);
	this->UpdateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		this->KeyTime(dt);
		this->UpdateEditorInput(dt);
		this->updateGui(dt);
	}
	else
	{
		this->pmenu->update(this->MousePosWindow);
		this->updatePmenuButton();
	}
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
}
void EditorState::render(RenderTarget* target)
{	

	if (!target)
	{
		target = this->window;
	}
	target->setView(this->MainView);
	this->Tilemap->render(*target, this->MousePosGrid);
	this->Tilemap->renderDeferrent(*target);

	target->setView(this->window->getDefaultView());
	this->renderGui(target);
	if (paused)
	{
		target->setView(this->window->getDefaultView());
		this->renderPmenuButton(*target);
	}

}