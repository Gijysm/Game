#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Network.hpp>
#include <memory>
#include <algorithm>
#include <iostream>

#include "..//States/State.h"
#include "..//GUI/PauseMenu.h"
#include "..//Map/TileMap.h"
#include "../Socket/StatusNetworkServer.h"
#include "..//Player//Player.h"
#include "../Player/Enemys/Enemy.h"
#include "..//Player/PlayerGUI.h"

enum ONLINE_GAME_STATE { CLIENT = 1, SERVER = 2 };

struct MultiPlayer {
	string name;
	std::unique_ptr<Player> players;
	
	MultiPlayer() : players(nullptr) {}
	MultiPlayer(const string& n, Player* p) : name(n), players(p) {}
	
	// Заборонити копіювання
	MultiPlayer(const MultiPlayer&) = delete;
	MultiPlayer& operator=(const MultiPlayer&) = delete;
	
	// Дозволити переміщення
	MultiPlayer(MultiPlayer&&) = default;
	MultiPlayer& operator=(MultiPlayer&&) = default;
};

class Enemy;
class Player;
class PlayerGUI;
class sf::View;
class sf::Font;
class sf::RenderTexture;
class Tilemap;
class PauseMenu;

class GameState : public State
{
private:
	int mode;
	std::map<std::string, std::pair<float, float>> playerPositions;
	std::set<std::string> playersWhoSentMove;
	string clientName;
	std::unique_ptr<TcpSocket> clientSocket;
	std::vector<MultiPlayer> multiplayerPlayers;
	StatusNetworkServer netS;
	Packet packet;
	sf::View view;
	std::unique_ptr<TileMap> Tilemap;
	std::unique_ptr<PauseMenu> pmenu;
	Shader core_shader;
	sf::RenderTexture renderTexture;
	Sprite renderSprite;
	Texture Weapon;
	Vector2i viewPos;
	map<string, Texture> temp;
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<EnemySystem> Enemy_System;
	std::unique_ptr<PlayerGUI> playerGUI;
	sf::Font font;

	void createPlayers(float x, float y, const string& name);
	void InitClient();
	void InitServer();
	void InitView();
	void InitEnemy();
	void InitKeyBinds();
	void InitAnimations();
	void InitTexture();
	void InitShaders();
	void InitPlayers();
	void InitPlayerGUI();
	void InitEnemySystem();
	void InitFont();
	void InitPmenu();
	void InitTileMap();
	void InitDeferredRender();

public:
	GameState(StateData* state_data, const int state);
	virtual ~GameState();

	void UpdateMp(const float& dT);
	void updatePlayer(const float& dt);
	void updateEnemy(const float& dt);
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