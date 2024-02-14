#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKey)
	:State(window, supportedKey)
{
	this->InitFont();
	this->InitKeyBinds();
	this->BackGround.setSize(Vector2f(window->getSize().x, window->getSize().y));
	this->BackGround.setFillColor(Color::Red);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}


void MainMenuState::InitKeyBinds()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\MainMenuKey_binds.ini");

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

void MainMenuState::EndState()
{
	cout << "Ending_State" << "\n";
}

void MainMenuState::Update_Input(const float& dt)
{
	this->CheckForEnd();

}

void MainMenuState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->Update_Input(dt);
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->BackGround);
}
