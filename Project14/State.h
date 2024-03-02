#ifndef STATE_H
#define STATE_H
#include "Player.h"
class State
{
private:

protected:
	RenderWindow* window;
	bool Exit;
	bool paused;
	map<string, Texture> texture;


	stack<State*>* states;

	map<string, int>* supportedKey;
	map<string, int> KeyBinds;

	Vector2i MousePosScreen;
	Vector2i MousePosWindow;
	Vector2f MousePosView;
public:
	State(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~State();

	virtual void UpdateMousePosition();
	virtual void InitKeyBinds() = 0;
	const bool& GetQuit() const;

	void EndState();
	void PausedState();
	void UnPausedState();

	virtual void Update_Input(const float& dt) = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
#endif
