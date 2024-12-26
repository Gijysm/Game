#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "..//States/State.h"
#include "..//GUI/PauseMenu.h"
#include "..//Map/TileMap.h"
#include "..//Player//Player.h"
#include "../Player/Enemys/Enemy.h"
#include "../Player/Enemys/Enemys_Include.h"
#include "..//Player/PlayerGUI.h"

class Enemy;
class Player;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;
class Tilemap;
class PauseMenu;

class GameState:public State
{
private:
	sf::View view;
	TileMap* Tilemap;
	PauseMenu* pmenu;
	Shader core_shader;
	sf::RenderTexture renderTexture;
	Sprite renderSprite;
	Texture Weapon;
	Vector2i viewPos;
	map<string, Texture> temp;
	Player* player;
	vector<Enemy*> enemies;
	PlayerGUI* playerGUI;
	sf::Font font;
	void InitView();
	void InitEnemy();
	void InitKeyBinds();
	void InitAnimations();
	void InitTexture();
	void InitShaders();
	void InitPlayers();
	void InitPlayerGUI();
	void InitFont();
	void InitPmenu();
	void InitTileMap();
	void InitDeferredRender();
public:
	GameState(StateData* satate_data);
	virtual ~GameState();

	void UpdatePlayerInput(const float& dt);
	void UpdateTileMap(const float& dt);
	void UpdateView(const float& dt);
	void updateButtons();
	void updatePlayerGUI(const float& dt);
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif