#include "GameState.h"

void GameState::InitTexture()
{
	temp["Idle"].loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Hero.png");
	this->texture["Idle"] = temp["Idle"];
	temp["Run"].loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\All_Texture\\Player\\Run.png");
	this->texture["Run"] = temp["Run"];
}

void GameState::InitPlayers()
{
	this->player = new Player(100, 50, this->temp);
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
