#include "State.h"

State::State(RenderWindow* window, map<string, int>* supportedKey)
{
	this->window = window;
	this->Wants_end = false;
	this->supportedKey = supportedKey;
}

State::~State()
{
}

void State::CheckForEnd()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))))
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
