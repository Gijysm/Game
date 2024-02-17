#include "GameState.h"

void GameState::InitTexture()
{
	Texture temp;
	temp.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Hero.png");
	this->texture["Player_Idle"] = temp;
}

void GameState::InitPlayers()
{
	this->player = new Player(0, 0, &this->texture["Player_Idle"]);
}

GameState::GameState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
	:State(window, supportedKey, states)
{
	this->InitKeyBinds();
	this->InitTexture();
	this->InitPlayers();
}

GameState::~GameState()
{
	delete this->player;
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

void GameState::EndState()
{
	cout << "Ending_State" << "\n";
}

void GameState::Update_Input(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_LEFT"))))
	{
		player->move(dt, -1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_RIGHT"))))
	{
		player->move(dt, 1.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_UP"))))
	{
		player->move(dt, 0.f, -1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_DOWN"))))
	{
		player->move(dt, 0.f, 1.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))))
	{
		this->GetQuit();
	}
}

void GameState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->Update_Input(dt);
	this->player->update(dt);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
		this->player->render(target);
}
