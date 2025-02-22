#include "..//stdafx.h"
#include "Player.h"

void Player::InitVariables()
{
    Attacking = false;
}

void Player::InitAnnimations()
{
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

AtributeComponent* Player::getAtributeComponent()
{
    return this->atributeComponent;
}

Player::Player(float x, float y, map < string, Texture>& texture_sheet, Texture& Weapon)
{
    
	this->InitVariables();

    this->CreateHitBoxComponent(this->sprite, 50, 55, 55, 55);
	this->CreateMovementComponent(300.f, 1500.f, 500.f);
	this->CreateAnimationComponent(texture_sheet);
    this->CreateSkillComponent();
    cout << this->skillComponent->getSkillLevel(SKILLS::Health) << endl;
    this->createAtributeComponent(0);
    this->SetPosition(x, y);
    this->CreateWeapon(Weapon);
    this->InitAnnimations();
}


string Player::directionToString(Direction dir)
{
    switch (dir)
    {
    case Direction::Top:
        return "Top";
        break;
    case Direction::Right:
        return "Right";
        break;
    case Direction::Bottom:
        return "Bottom";
        break;
    case Direction::Left:
        return "Left";
        break;
    default:
        return "Bottom";
        break;
    }
	
}

Player::~Player()
{
}

void Player::updateAnimation(const float& dt)
{
    if (Mouse::isButtonPressed(Mouse::Button::Left)) // ?????? ????? !this->Attacking
    {
        this->Attacking = true;
    }
    if (this->Attacking)
    {
        if (this->animationComponent->play("Attack_" + directionToString(dir), dt, true))
            this->Attacking = false;
    }
    if (this->Movecomponent->GetStates(Idle))
    {
        this->animationComponent->play("Idle_" + directionToString(dir), dt);
    }
    else if (this->Movecomponent->GetStates(Moving_Right))
    {
        this->animationComponent->play("Run_Right", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
        dir = Direction::Right;
    }
    else if (this->Movecomponent->GetStates(Moving_Left))
    {
        this->animationComponent->play("Run_Left", dt, this->Movecomponent->GetVelocity().x, this->Movecomponent->GetMaxVelocity());
        dir = Direction::Left;

    }
    else if (this->Movecomponent->GetStates(Moving_Down))
    {
        this->animationComponent->play("Run_Bottom", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
        dir = Direction::Bottom;

    }
    else if (this->Movecomponent->GetStates(Moving_Up))
    {
        this->animationComponent->play("Run_Top", dt, this->Movecomponent->GetVelocity().y, this->Movecomponent->GetMaxVelocity());
        dir = Direction::Top;
    }
}

void Player::update(const float& dt, Vector2f& mouse_view_pos)
{
    this->Movecomponent->update(dt);
    this->peak->updatePosition(dt, mouse_view_pos,Vector2f(this->getCenter().x, this->getPosition().y));

    this->updateAnimation(dt);
   
    if (Keyboard::isKeyPressed(Keyboard::E)) // ?????? ????? !this->Attacking
    {
        this->atributeComponent->gainExp(20);
    }

    this->hitboxComponent->update();
}

void Player::render(RenderTarget& target, Shader* shader, const bool showCol, const Vector2f Light_Position)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", Light_Position);
        target.draw(this->sprite, shader);

        this->peak->render(target, shader, Light_Position);
    }
    else
    {
        target.draw(this->sprite);
        this->peak->render(target);
        
    }
    if(showCol)
    {
        this->hitboxComponent->render(target);
    }
}
