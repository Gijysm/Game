#include "Player.h"

void Player::InitVariables()
{
}

void Player::InitComponent()
{
	this->CreateMovementComponent(290.f);
}

Player::Player(float x, float y, Texture* texture)
{
	this->InitVariables();
	this->InitComponent();

	this->CreateSprite(texture);
	this->SetPosition(x, y);
}

Player::~Player()
{
}
