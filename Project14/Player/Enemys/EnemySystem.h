#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H
#include "../../Map/EnemySpawnerTile.h"
#include "../Enemys/Spider.h"
#include <memory>

enum EnemyTypes{Spiders = 0}; 

class EnemySystem
{
private:
    map<string, Texture>& Textures;
    vector<std::unique_ptr<Enemy>>& ActiveEnemy;
public:
    EnemySystem(vector<std::unique_ptr<Enemy>>& ActiveEnemy,
          map<string, Texture>& Textures);
    virtual ~EnemySystem();

    void CreateEnemy(const short enemy_type, const float xPos, const float yPos, const string& name_animate);

    void update(const float& dt);
    void render(RenderTarget* target = NULL);
};
#endif
