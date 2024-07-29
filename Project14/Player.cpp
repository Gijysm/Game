#include "stdafx.h"
#include "Player.h"

void Player::InitVariables()
{
    Attacking = false;
}

AtributeComponent* Player::getAtributeComponent()
{
    return this->atributeComponent;
}

Player::Player(float x, float y, map < string, Texture>& texture_sheet)
{
    
	this->InitVariables();

	this->SetPosition(x, y);

    this->CreateHitBoxComponent(this->sprite, 140, 42, 55, 115);
	this->CreateMovementComponent(300.f, 1500.f, 500.f);
	this->CreateAnimationComponent(texture_sheet);
    this->createAtributeComponent(0);
    this->animationComponent->addAnimation("Idle_Top", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Idle_Left", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Idle_Right", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Idle_Bottom", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Run_Top", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Run_Left", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Run_Right", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Run_Bottom", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Attack_Top", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Attack_Left", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Attack_Right", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Attack_Bottom", 10.f, 0, 0, 6, 0, 64, 64);
}

void Player::loseHP(const int hp)
{
    this->atributeComponent->hp -= hp;
    if (this->atributeComponent->hp < 0)
    {
		this->atributeComponent->hp = 0;
	}
}

void Player::gainHP(const int hp)
{
    	this->atributeComponent->hp += hp;
        if (this->atributeComponent->hp > this->atributeComponent->hpMax)
        {
		this->atributeComponent->hp = this->atributeComponent->hpMax;
	}
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
        if (this->animationComponent->play("Attack_Top", dt, true))
            this->Attacking = false;
    }
    if (this->Movecomponent->GetStates(Idle))
    {
        this->animationComponent->play("Idle_Top", dt);
    }
    else if (this->Movecomponent->GetStates(Moving_Right))
    {
        this->animationComponent->play("Run_Right", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Left))
    {
        this->animationComponent->play("Run_Left", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Down))
    {
        this->animationComponent->play("Run_Bottom", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
    }
    else if (this->Movecomponent->GetStates(Moving_Up))
    {
        this->animationComponent->play("Run_Top", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
    }
    if (Keyboard::isKeyPressed(Keyboard::E)) // ?????? ????? !this->Attacking
    {
        this->atributeComponent->gainExp(20);
    }

    this->hitboxComponent->update();
}

void Player::render(RenderTarget& target)
{
    target.draw(this->sprite);
    this->hitboxComponent->render(target);
}
