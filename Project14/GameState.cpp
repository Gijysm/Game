#include "GameState.h"

GameState::GameState(RenderWindow* window):State(window)
{
}

GameState::~GameState()
{
}


void GameState::EndState()
{
	cout << "Ending_State" << "\n";
}

void GameState::Update_Key_Binds(const float& dt)
{
	this->CheckForEnd();
}

void GameState::update(const float& dt)
{
	this->Update_Key_Binds(dt);
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		cout << "A" << "\n";
	}
}

void GameState::render(RenderTarget* target)
{
}
