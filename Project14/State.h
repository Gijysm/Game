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
	map<string, int>* supportedKey;
	map<string, int> KeyBinds;
public:
	State(RenderWindow* window, map<string, int>* supportedKey);
	virtual ~State();


	virtual void InitKeyBinds() = 0;
	virtual void CheckForEnd();
	const bool& GetQuit() const;

	virtual void EndState() = 0;
	virtual void Update_Input(const float& dt) = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
#endif
