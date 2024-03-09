#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState:public State
{
private:
	PauseMenu* pmenu;
	map<string, Texture> temp;
	Player* player;
	Font font;
	void InitKeyBinds();
	void InitTexture();
	void InitPlayers();
public:
	GameState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~GameState();

	void UpdatePlayerInput(const float& dt);
	void InitFont();
	void InitPmenu();
	
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif