#ifndef STATE_H
#define STATE_H
#include "..//Graphics//GraphicsSettings.h"

class Player;
class GraphicsSettings;  
class State;

class StateData
{
private:

public:
	StateData() {};
	float GridSize;
	RenderWindow* window;
	GraphicsSettings* GFXSettings;
	map<string, int>* supportedKey; 
	stack<State*>* states;
};
class State
{
private:

protected:
	bool Exit;
	bool paused;
	RenderWindow* window;

	stack<State*>* states;
	GraphicsSettings* GfxSettings;
	StateData* Statedata;

	map<string, int>* supportedKey;
	map<string, int> KeyBinds;
	float Keytime;
	float KeytimeMax;
	float gridSize; 

	Vector2i MousePosScreen;
	Vector2i MousePosWindow;
	Vector2f MousePosView;
	Vector2i MousePosGrid;
public:
	VideoMode vm;
	State(StateData* state_data);
	virtual ~State();

	const bool& GetQuit() const;
	const bool GetKeyTime();

	virtual void UpdateMousePosition(View* view = NULL);
	virtual void InitKeyBinds();
	virtual void UpdateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;


	void EndState();
	void PausedState();
	void UnPausedState();


	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target = NULL) = 0;
};
#endif
