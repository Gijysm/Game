#include "stdafx.h"
#include "State.h"

State::State(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
{
	this->window = window;
	this->Exit = false;
	this->paused = false;
	this->states = states;
	this->supportedKey = supportedKey;
	this->Keytime = 0;
	this->KeytimeMax = 3;
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

void State::InitKeyBinds()
{
}

void State::UpdateKeyTime(const float& dt)
{
	if (this->Keytime < this->KeytimeMax)
	{
		this->Keytime += 10 * dt;
	}
}


const bool& State::GetQuit() const
{
	return this->Exit;
}

const bool State::GetKeyTime()
{
	if (this->Keytime > this->KeytimeMax)
	{
		this->Keytime = 0;
		return true;
	}
	return false;
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
