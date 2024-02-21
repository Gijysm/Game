#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"

class GameState:public State
{
private:
	map<string, Texture> temp;
	Player* player;
	void InitKeyBinds();
	void InitTexture();
	void InitPlayers();
public:
	GameState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~GameState();

	void EndState();
	void Update_Input(const float& dt);
	
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif