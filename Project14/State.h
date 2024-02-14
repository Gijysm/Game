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

using namespace sf;
using namespace std;

class State
{
private:
	vector<Texture> texture;

public:
	State();
	virtual ~State();

	virtual void update() = 0;
	virtual void render() = 0;
};
#endif
