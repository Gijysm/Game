#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stack>
#include <map>

#include "Button.h"

using namespace sf;
using namespace std;

class PauseMenu
{
private:
	Text MenuText;
	Font& Menufont;

	RectangleShape BackGround;
	RectangleShape container;

	map<string, Button*> PauseMenu_Btn;
public:
	PauseMenu(RenderWindow& window, Font& font);
	virtual ~PauseMenu();
	map<string, Button*>& GetButtons();

	const bool isButtonPressed(const string& key);
	void AddButtons(const string& key, const float& y, const string& name);
	void update(const Vector2f& mousePosition);
	void render(RenderTarget& target);
};

#endif