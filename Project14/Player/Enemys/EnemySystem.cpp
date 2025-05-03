#include "..//..//stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(vector<std::unique_ptr<Enemy>>& ActiveEnemy,
                   map<string, Texture>& Textures)
                       :Textures(Textures), ActiveEnemy(ActiveEnemy)
{
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::CreateEnemy(const short enemy_type, const float xPos, const float yPos, const string& name_animate)
{
    switch(enemy_type)
    {
    case EnemyTypes::Spiders:
        this->ActiveEnemy.push_back(std::make_unique<Spider>(xPos, yPos, this->Textures[name_animate], name_animate));
        break;
    default:
        cerr << "ERROR::CREATE_ENEMY::ENEMY_TYPE_DOESNT_HAVE" << endl;
        break;
    }
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(RenderTarget* target)
{
    if(target)
    {
        for(auto& enemy : this->ActiveEnemy)
        {
            enemy->render(*target);
        }
    }
}