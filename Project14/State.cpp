#include "State.h"

State::State(RenderWindow* window)
{
	this->window = window;
	this->Wants_end = false;
}

State::~State()
{
}

void State::CheckForEnd()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		this->Wants_end = true;
}

const bool& State::GetQuit() const
{
	return this->Wants_end;
}

void State::update(const float& dt)
{
}

void State::render(RenderTarget* target)
{
}
