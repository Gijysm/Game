#include "stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->InitVariables();
	this->InitBackGround();
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
}


void EditorState::InitVariables()
{
	this->paused = false;
	this->Texture_rect = IntRect(0, 0, static_cast<int>(16), static_cast<int>(16));
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
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->AddButtons("RESUME", 250, "Resume");
	this->pmenu->AddButtons("SAVE", 350, "SAVE");
	this->pmenu->AddButtons("LOAD", 450, "Load");
	this->pmenu->AddButtons("QUIT", 550, "Quit");
}

void EditorState::InitTileMap()
{
	this->Tilemap = new TileMap(this->Statedata->GridSize, 100, 100);
}

void EditorState::InitGui()
{
	this->SelectorRect.setSize(Vector2f(this->Statedata->GridSize, this->Statedata->GridSize));
	this->SelectorRect.setFillColor(Color(255,255,255,150));
	this->SelectorRect.setOutlineThickness(1);
	this->SelectorRect.setOutlineColor(Color::Green);

	this->SelectorRect.setTexture(this->Tilemap->getTileSheet());
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
	
}

void EditorState::KeyTime(const float& dt)
{
	//if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_LEFT"))))
	//{
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_RIGHT"))))
	//{
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_UP"))))
	//{
	//}
	//if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_DOWN"))))
	//{
	//}

}

void EditorState::updatePmenuButton()
{
	if (this->pmenu->isButtonPressed("RESUME"))
	{
		this->UnPausedState();
	}
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->EndState();
	}
}

void EditorState::updateButton()
{
}

void EditorState::updateGui()
{
	this->SelectorRect.setPosition(this->MousePosGrid.x * this->Statedata->GridSize, this->MousePosGrid.y * this->Statedata->GridSize);
	this->SelectorRect.setTextureRect(this->Texture_rect);
	stringstream ss;
	this->CursorText.setPosition(MousePosView + Vector2f(15, 10));
	ss << MousePosView.x << " " << MousePosView.y << "\n" << this->Texture_rect.left << " " << this->Texture_rect.width
		<< "\n" << this->Texture_rect.top << " " << this->Texture_rect.height;
	this->CursorText.setString(ss.str());
}

void EditorState::UpdateEditorInput(const float& dt)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime())
	{
		this->Tilemap->AddTile(this->MousePosGrid.x, this->MousePosGrid.y, 0, this->Texture_rect);
	}
	if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime())
	{
		this->Tilemap->RemoveTile(this->MousePosGrid.x, this->MousePosGrid.y, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && this->GetKeyTime() && this->Texture_rect.left < 384)
	{
		this->Texture_rect.left += 16;
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
	target->draw(this->SelectorRect);
	target->draw(this->CursorText);
}

void EditorState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->UpdateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		this->KeyTime(dt);
		this->UpdateEditorInput(dt);
		this->updateGui();
	}
	else
	{
		this->pmenu->update(this->MousePosView);
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
	this->Tilemap->render(*target);
	target->draw(this->CursorText);
	this->renderGui(target);
	if (paused)
	{
		this->renderPmenuButton(*target);
	}

}