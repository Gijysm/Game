#include "stdafx.h"
#include "Game.h"

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->Statedata));
}

void Game::InitWindow()
{
	if (this->GFXSettings.fullscreen)
	{
		this->window = new RenderWindow(GFXSettings.resolution, GFXSettings.title, Style::Fullscreen, this->GFXSettings.Context_Settings);
	}
	else
	{
		this->window = new RenderWindow(GFXSettings.resolution, GFXSettings.title, Style::Titlebar | Style::Close, this->GFXSettings.Context_Settings);
	}
	this->window->setFramerateLimit(this->GFXSettings.FrameRateLimit);
	this->window->setVerticalSyncEnabled(this->GFXSettings.Vertical_sync);
}

Game::Game()
{
	this->InitVariabes();
	this->InitGraphicsSettings();
	this->InitWindow();
	this->InitKeys();
	this->InitStateData();        
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::InitKeys()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\Sup_Keys.ini");

	if (ifs.is_open())
	{
		string key = "";
		int Key_value = 0;

		while (ifs >> key >> Key_value)
		{
			this->supportedKey[key] = Key_value;
		}
	}
	for (auto i : supportedKey)
	{
		if (i.first != "Escape")
		{
			cout << i.first << "      " << i.second << "\n";
		}
		else
		{
			cout << i.first << " " << i.second << "\n";
		}
	}
}

void Game::updateSFMLEvent()
{

	while (this->window->pollEvent(this->event))
	{
		// "close requested" event: we close the window
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::InitVariabes()
{
	this->window = NULL;
	this->dt = 0;
	this->GridSize = 64;
}

void Game::InitStateData()
{
	this->Statedata.window = this->window;
	this->Statedata.GFXSettings = &this->GFXSettings;
	this->Statedata.supportedKey = &this->supportedKey;
	this->Statedata.states = &this->states;
	this->Statedata.GridSize = this->GridSize;
}

void Game::InitGraphicsSettings()
{
	this->GFXSettings.LoadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Config\\Wincon.ini");

}

void Game::UpdateDt()
{
	this->dt = this->Clockdt.restart().asSeconds();
}

void Game::update()
{
	this->updateSFMLEvent();

	if (!this->states.empty())
	{
		if (this->window->hasFocus()) {
			this->states.top()->update(this->dt);

			if (this->states.top()->GetQuit())
			{
				this->states.top()->EndState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		this->EndApplication();
		this->window->close();
	}
}


void Game::EndApplication()
{
	cout << "End Application" << "\n";
}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->UpdateDt();
		this->update();
		this->render();
	}
}
