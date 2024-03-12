#include "stdafx.h"
#include "Game.h"

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKey, &this->states));
}

void Game::InitWindow()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\Wincon.ini");
	string title = "None";
	VideoMode windowBoundes = VideoMode::getDesktopMode();
	bool fullscreenmode = false;
	unsigned Frame = 120;
	bool Vertical_sync_enabled = false;
	unsigned antializing_lvl = 0;
	
	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> windowBoundes.width >> windowBoundes.height;
		ifs >> fullscreenmode;
		ifs >> Frame;
		ifs >> Vertical_sync_enabled;
		ifs >> antializing_lvl;
	}
	else
	{
		throw "Error";
		ifs.close();
	}
	ifs.close();

	this->fullscreenmode = fullscreenmode;

	Window_Settings.antialiasingLevel = antializing_lvl;
	if(this->fullscreenmode)
	{
		this->window = new RenderWindow(windowBoundes, title, Style::Fullscreen, Window_Settings);
	}
	else
	{
		this->window = new RenderWindow(windowBoundes, title, Style::Titlebar | Style::Close, Window_Settings);
	}
	this->window->setFramerateLimit(Frame);
	this->window->setVerticalSyncEnabled(Vertical_sync_enabled);
}

Game::Game()
{
	this->InitWindow();
	this->InitKeys();
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
		if(i.first != "Escape")
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

void Game::UpdateDt()
{
	this->dt = this->Clockdt.restart().asSeconds();
}

void Game::update()
{
	this->updateSFMLEvent();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
	
		if (this->states.top()->GetQuit())
		{
			this->states.top()->EndState();
			delete this->states.top();
			this->states.pop();
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
