#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->Statedata = state_data;
	this->window = state_data->window;
	this->Exit = false;
	this->paused = false;
	this->states = state_data->states;
	this->supportedKey = state_data->supportedKey;
	this->Keytime = 0;
	this->KeytimeMax = 3;
	this->gridSize = state_data->GridSize;
}

State::~State()
{
}

void State::UpdateMousePosition(View* view)
{
	this->MousePosScreen = Mouse::getPosition();
	this->MousePosWindow = Mouse::getPosition(*this->window);
	if(view)
		this->window->setView(*view);
	this->MousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
	this->MousePosGrid = Vector2i(
		static_cast<int>(this->MousePosView.x) / static_cast<int>(this->gridSize),
		static_cast<int>(this->MousePosView.y) / static_cast<int>(this->gridSize)
	);
	this->window->setView(this->window->getDefaultView());
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

const float State::p2pX(const float perc)
{
	return std::floor(static_cast<float>(this->Statedata->GFXSettings->resolution.width) * (perc / 100.f));
}

const float State::p2pY(const float perc)
{
	return std::floor(static_cast<float>(this->Statedata->GFXSettings->resolution.height) * (perc / 100.f));
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
