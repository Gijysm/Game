#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState:public State
{
private:
	TileMap* Tilemap;
	PauseMenu* pmenu;
	map<string, Texture> temp;
	Player* player;
	Font font;
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
	
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif