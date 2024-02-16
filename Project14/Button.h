#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>


using namespace sf;
using namespace std;

enum Button_States{BTN_IDLE = 0, 
BTN_HOWER, BTN_ACTIVE};

class Button
{
private:
	short unsigned Button_State;

	bool Hower;
	bool Active;

	RectangleShape Shape;
	Font* font;
	Text Text;

	Color Idle_Color;
	Color Hower_Color;
	Color Active_Color;
public:
	Button(float x, float y, float Width, float height,
		Font* font, string text,
		Color idle_Color, Color hower_Color, Color active_Color);
	virtual ~Button();

	const bool isPressed() const;

	void update(const Vector2f MousePos);

	virtual void render(RenderTarget* target);
};

#endif // !BUTTON_H