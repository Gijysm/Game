#include "Player.h"

void Player::InitVariables()
{
}

void Player::InitComponent()
{
	this->CreateMovementComponent(500.f, 15,5);
}

Player::Player(float x, float y, Texture& texture_sheet)
{
	this->InitVariables();

	this->SetPosition(x, y);
	this->CreateMovementComponent(300.f, 30.f, 5.f);
	this->CreateAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 1.f, 0, 0, 2, 4, 128, 64);
}

Player::~Player()
{
}
void Player::update(const float& dt)
{
    Entity::update(dt);

        this->animationComponent->play("IDLE", dt);
}