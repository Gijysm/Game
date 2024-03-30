#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class Player;
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
	RenderTexture renderTexture;
	Sprite renderSprite;
	map<string, Texture> temp;
	Player* player;
	Font font;
	void InitView();
	void InitKeyBinds();
	void InitTexture();
	void InitPlayers();
public:
	GameState(StateData* satate_data);
	virtual ~GameState();

	void UpdatePlayerInput(const float& dt);
	void InitFont();
	void InitPmenu();
	void InitTileMap();
	void InitDeferredRender();
	void UpdateView(const float& dt);
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif