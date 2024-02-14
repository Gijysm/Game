#ifndef STATE_H
#define STATE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>

using namespace sf;
using namespace std;

class State
{
private:
	RenderWindow* window;
	bool Wants_end;
	vector<Texture> texture;

public:
	State(RenderWindow* window);
	virtual ~State();

	virtual void CheckForEnd();
	const bool& GetQuit() const;

	virtual void EndState() = 0;
	virtual void Update_Key_Binds(const float& dt) = 0;

	virtual void update(const float& dt) = 0;
	virtual void render(RenderTarget* target) = 0;
};
#endif
