#include "stdafx.h"
#include "GameState.h"


void GameState::InitTexture()
{
	temp["Idle"].loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Idle.png");
	this->texture["Idle"] = temp["Idle"];
	temp["Run"].loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Run.png");
	this->texture["Run"] = temp["Run"];
	temp["Attack"].loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Attacks.png");
	this->texture["Attack"] = temp["Attack"];
}

void GameState::InitPlayers()
{
	this->player = new Player(500, 400, this->temp);
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->InitView();
	this->InitTileMap();
	this->InitDeferredRender();
	this->InitFont();
	this->InitKeyBinds();
	this->InitTexture();
	this->InitPmenu();
	this->InitPlayers();
}
void GameState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}
void GameState::InitPmenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	this->pmenu->AddButtons("RESUME", 250, "Resume");
	this->pmenu->AddButtons("SAVE", 350, "SAVE");
	this->pmenu->AddButtons("LOAD", 450, "Load");
	this->pmenu->AddButtons("QUIT", 550, "Quit");
}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->Tilemap;
}


void GameState::InitKeyBinds()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\Key_binds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string Key2 = "";

		while (ifs >> key >> Key2)
		{
			this->KeyBinds[key] = this->supportedKey->at(Key2);
		}
	}
	ifs.close();
}

void GameState::UpdatePlayerInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_LEFT"))))
	{
		player->move(-1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_RIGHT"))))
	{
		player->move(1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_UP"))))
	{
		player->move(0.f, -1.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_DOWN"))))
	{
		player->move(0.f, 1.f, dt);
	}

}

void GameState::InitDeferredRender()
{
	this->renderTexture.create(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0, 
		this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
}

void GameState::UpdateView(const float& dt)
{
	this->view.setCenter(this->player->getPosition());
}

void GameState::updateInput(const float& dt)
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

void GameState::update(const float& dt)
{
	this->UpdateMousePosition(&this->view);
	this->UpdateKeyTime(dt);
	this->updateInput(dt);
	if(!this->paused)
	{
		this->UpdateView(dt);
		this->UpdatePlayerInput(dt);
		this->player->update(dt);
	}
	else
	{
		this->pmenu->update(this->MousePosWindow);
		this->updateButtons();
	}
}

void GameState::updateButtons()
{
	if (this->pmenu->isButtonPressed("RESUME"))
	{
		this->UnPausedState();
	}
	if (this->pmenu->isButtonPressed("QUIT") && this->GetKeyTime())
	{
		this->EndState();
	}
}

void GameState::InitView()
{
	this->view.setSize(Vector2f(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
	this->view.setCenter(this->Statedata->GFXSettings->resolution.width / 2.f,
		this->Statedata->GFXSettings->resolution.height / 2.f);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	this->renderTexture.clear();
	this->renderTexture.setView(this->view);
	this->Tilemap->render(renderTexture);
	this->player->render(this->renderTexture);
	if (this->paused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

void GameState::InitTileMap()
{
	this->Tilemap = new TileMap(this->Statedata->GridSize, 16, 16, 60, 60, "C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Grass\\GRASS.png");
	this->Tilemap->loadFromFile("ѕук.txt");
}
