#include "Player.h"

void Player::InitVariables()
{
}

Player::Player(float x, float y, map < string, Texture>& texture_sheet)
{
	this->InitVariables();

	this->SetPosition(x, y);
    this->CreateHitBoxComponent(this->sprite, 155, 50, 74, 138);
	this->CreateMovementComponent(300.f, 30.f, 5.f);
	this->CreateAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("Idle", 1.f, 0, 0, 2, 4, 128, 64);
    this->animationComponent->addAnimation("Run", 1.f, 0, 0, 2, 4, 128, 64);
}

Player::~Player()
{
}
void Player::update(const float& dt)
{
        this->Movecomponent->update(dt);

        if (this->Movecomponent->GetStates(Idle))
        {
            this->animationComponent->play("Idle", dt);
        }
        if (this->Movecomponent->GetStates(Moving_Right))
        {
            this->animationComponent->play("Run", dt);
        }
        this->hitboxComponent->update();
}