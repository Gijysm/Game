#ifndef STATE_H
#define STATE_H
#include "Entity.h"
class State
{
private:

protected:
	RenderWindow* window;
	bool Wants_end;
	vector<Texture> texture;

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
	virtual void CheckForEnd();
	const bool& GetQuit() const;

	virtual void EndState() = 0;
	virtual void Update_Input(const float& dt) = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
#endif
