#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
class GameState:public State
{
private:

public:
	GameState(RenderWindow* window);
	virtual ~GameState();

	void EndState();
	void Update_Key_Binds(const float& dt);
	
	void update(const float& dt);
	void render(RenderTarget* target);
};

#endif