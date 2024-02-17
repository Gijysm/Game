#include "State.h"

State::State(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
{
	this->window = window;
	this->Wants_end = false;
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
	return this->Wants_end;
}

void State::EndState()
{
	this->Wants_end = true;
}

void State::update(const float& dt)
{
}

void State::render(RenderTarget* target)
{
}
