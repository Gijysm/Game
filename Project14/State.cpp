#include "State.h"

State::State(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
{
	this->window = window;
	this->Exit = false;
	this->paused = false;
	this->states = states;
	this->supportedKey = supportedKey;
}

State::~State()
{
}

void State::UpdateMousePosition()
{
	this->MousePosScreen = Mouse::getPosition();
	this->MousePosWindow = Mouse::getPosition(*this->window);
	this->MousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}


const bool& State::GetQuit() const
{
	return this->Exit;
}

void State::EndState()
{
	this->Exit = true;
}

void State::PausedState()
{
	this->paused = true;
}

void State::UnPausedState()
{
	this->paused = false;
}

void State::update(const float& dt)
{
}

void State::render(RenderTarget* target)
{
}
