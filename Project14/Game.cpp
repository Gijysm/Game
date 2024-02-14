#include "Game.h"

void Game::InitWindow()
{
	this->window = new RenderWindow(VideoMode(800, 600), "My window");
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
