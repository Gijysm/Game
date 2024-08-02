#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

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
	View view;
	TileMap* Tilemap;
	PauseMenu* pmenu;
	Shader core_shader;
	RenderTexture renderTexture;
	Sprite renderSprite;
	map<string, Texture> temp;
	Player* player;
	PlayerGUI* playerGUI;
	Font font;
	void InitView();
	void InitKeyBinds();
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