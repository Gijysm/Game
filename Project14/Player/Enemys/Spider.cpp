#include "..//..//stdafx.h"
#include "Spider.h"
void Spider::InitVariables()
{
    Attacking = false;
}

void Spider::InitComponent()
{
    Enemy::InitComponent();
}

void Spider::InitAnnimations()
{
    this->animationComponent->addAnimation("Enemy_Idle_Top", 10.f, 0, 0, 4, 0, 32, 32);
    this->animationComponent->addAnimation("Enemy_Idle_Left", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Idle_Right", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Idle_Bottom", 10.f, 0, 0, 11, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Run_Top", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Run_Left", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Run_Right", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Run_Bottom", 8.f, 0, 0, 5, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Attack_Top", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Attack_Left", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Attack_Right", 10.f, 0, 0, 6, 0, 64, 64);
    this->animationComponent->addAnimation("Enemy_Attack_Bottom", 10.f, 0, 0, 6, 0, 64, 64);
}
Spider::Spider(float x, float y,
    std::map<std::string, sf::Texture>& textures,
    sf::Texture texture)
{
        
    this->InitVariables();
    this->CreateHitBoxComponent(this->sprite, 50, 55, 55, 55);
    this->CreateMovementComponent(300.f, 1500.f, 500.f);
    this->CreateAnimationComponent(textures);
    this->CreateSkillComponent();
    // cout << this->skillComponent->getSkillLevel(SKILLS::Health) << endl;
    // this->createAtributeComponent(0);
    this->SetPosition(x, y);
    // this->CreateWeapon(Weapon);
    this->InitAnnimations();
}

Spider::~Spider()
{
}
void Spider::updateAnimation(const float& dt)
{
    this->animationComponent->play("Enemy_Idle_Top", dt);
}

void Spider::update(const float& dt, Vector2f& mouse_view_pos)
{
    this->Movecomponent->update(dt);
    this->updateAnimation(dt);
    // this->peak->updatePosition(dt, mouse_view_pos,Vector2f(this->getCenter().x, this->getPosition().y));
    this->hitboxComponent->update();
}
void Spider::update(const float& dt)
{
    this->Movecomponent->update(dt);
    this->updateAnimation(dt);
    // this->peak->updatePosition(dt, mouse_view_pos,Vector2f(this->getCenter().x, this->getPosition().y));
    this->hitboxComponent->update();
}

void Spider::render(RenderTarget& target, Shader* shader, const bool Show_col, const Vector2f Light_Position)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", Light_Position);
        target.draw(this->sprite, shader);

        // this->peak->render(target, shader, getCenter());
    }
    else
    {
        target.draw(this->sprite);
        // this->peak->render(target);
    }
    if(Show_col)
    {
        this->hitboxComponent->render(target);
    }
}