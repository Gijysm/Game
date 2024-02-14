#include "Game.h"

void Game::InitWindow()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\Wincon.ini");
	string title = "None";
	VideoMode Wind_bound(1280, 720);
	unsigned Frame = 120;
	bool Vertical_sync_enabled = false;
	
	if (ifs.is_open())
	{
		getline(ifs, title);
		ifs >> Wind_bound.width >> Wind_bound.height;
		ifs >> Frame;
		ifs >> Vertical_sync_enabled;
	}
	else
	{
		throw "Error";
		ifs.close();
	}
	ifs.close();

	this->window = new RenderWindow(Wind_bound, title);
	this->window->setFramerateLimit(Frame);
	this->window->setVerticalSyncEnabled(Vertical_sync_enabled);
}

Game::Game()
{
	this->InitWindow();
}

Game::~Game()
{
	delete this->window;
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
	this->dt = this->Clockdt.getElapsedTime().asSeconds();
	system("cls");
	cout << this->dt << "\n";
}

void Game::update()
{
	this->updateSFMLEvent();
}

void Game::render()
{
	this->window->clear();
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
