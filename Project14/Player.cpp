#include "stdafx.h"
#include "Player.h"

void Player::InitVariables()
{
    Attacking = false;
}

Player::Player(float x, float y, map < string, Texture>& texture_sheet)
{
	this->InitVariables();

	this->SetPosition(x, y);

    this->CreateHitBoxComponent(this->sprite, 155, 50, 74, 138);
	this->CreateMovementComponent(350.f, 30.f, 5.f);
	this->CreateAnimationComponent(texture_sheet);
    this->animationComponent->addAnimation("Idle", 10.f, 0, 0, 2, 4, 128, 64);
    this->animationComponent->addAnimation("Run", 8.f, 0, 0, 2, 4, 128, 64);
    this->animationComponent->addAnimation("Attack", 10.f, 0, 0, 8, 1, 128, 64);
}

Player::~Player()
{
}
void Player::update(const float& dt)
{
    this->Movecomponent->update(dt);

    if (Mouse::isButtonPressed(Mouse::Button::Left)) // ?????? ????? !this->Attacking
    {
        this->Attacking = true;
    }
    if (this->Attacking)
    {
        if (this->animationComponent->play("Attack", dt, true))
            this->Attacking = false;
    }
    if (this->Movecomponent->GetStates(Idle))
    {
        this->animationComponent->play("Idle", dt);
    }
    else if (this->Movecomponent->GetStates(Moving_Right))
    {
        this->sprite.setOrigin(0, 0);
        this->sprite.setScale(3, 3);
        this->animationComponent->play("Run", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Left))
    {
        this->sprite.setOrigin(130, 0);
        this->sprite.setScale(-3, 3);
        this->animationComponent->play("Run", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Down))
    {
        this->animationComponent->play("Run", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Up))
    {
        this->animationComponent->play("Run", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
    }

    this->hitboxComponent->update();
}
