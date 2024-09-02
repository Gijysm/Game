#include "..//stdafx.h"
#include "Enemy.h"
void Enemy::InitVariables()
{
    Attacking = false;
}

void Enemy::InitAnnimations()
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

// AtributeComponent* Enemy::getAtributeComponent()
// {
//     return this->atributeComponent;
// }

Enemy::Enemy(EnemySpawner& spawner,float x, float y,
    map < string, Texture>& texture_sheet, Texture Weapon) : spawner(spawner)
{
    
	this->InitVariables();
    this->CreateHitBoxComponent(this->sprite, 50, 55, 55, 55);
	this->CreateMovementComponent(300.f, 1500.f, 500.f);
	this->CreateAnimationComponent(texture_sheet);
    this->CreateSkillComponent();
    // cout << this->skillComponent->getSkillLevel(SKILLS::Health) << endl;
    // this->createAtributeComponent(0);
    this->SetPosition(x, y);
    // this->CreateWeapon(Weapon);
    this->InitAnnimations();
}


// string Enemy::directionToString(Direction dir)
// {
//     switch (dir)
//     {
//     case Direction::Top:
//         return "Top";
//         break;
//     case Direction::Right:
//         return "Right";
//         break;
//     case Direction::Bottom:
//         return "Bottom";
//         break;
//     case Direction::Left:
//         return "Left";
//         break;
//     default:
//         return "Bottom";
//         break;
//     }
// 	
// }

Enemy::~Enemy()
{
}

void Enemy::updateAnimation(const float& dt)
{
    this->animationComponent->play("Idle_Top", dt);
}

void Enemy::update(const float& dt, Vector2f& mouse_view_pos)
{
    this->Movecomponent->update(dt);
    this->updateAnimation(dt);
    // this->peak->updatePosition(dt, mouse_view_pos,Vector2f(this->getCenter().x, this->getPosition().y));
    this->hitboxComponent->update();
}

void Enemy::render(RenderTarget& target, Shader* shader)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", this->getCenter());
        target.draw(this->sprite, shader);

        // this->peak->render(target, shader, getCenter());
    }
    else
    {
        target.draw(this->sprite);
        // this->peak->render(target);
        this->hitboxComponent->render(target);
    }
}

