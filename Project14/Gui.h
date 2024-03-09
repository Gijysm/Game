#ifndef GUI_H
#define GUI_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>


using namespace sf;
using namespace std;

enum Button_States{BTN_IDLE = 0, 
BTN_HOWER, BTN_ACTIVE};
namespace gui
{
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

		Color Text_idle_Color;
		Color Text_hower_Color;
		Color Text_active_Color;
	public:
		Button(float x, float y, float Width, float height,
			Font* font, string text, int Character_size,
			Color Text_idle_Color, Color Text_hower_Color, Color Text_active_Color,
			Color idle_Color, Color hower_Color, Color active_Color);
		virtual ~Button();

		const bool isPressed() const;
		const string getText() const;


		void setText(const string text);

		void update(const Vector2f& MousePos);
		void render(RenderTarget& target);
	};
	class DropDownList
	{
	private:
		Font& font;
		gui::Button* activeEllement;
		vector<gui::Button*> list;


		bool showlist;
		float Keytime;
		float KeytimeMax;
	public:
		DropDownList(float x, float y, float width, float height, Font& font,string list[],
			unsigned NOEllements, unsigned default_index = 0);
		~DropDownList();

		void UpdateKeyTime(const float& dt);
		const bool GetKeyTime();
		void update(const Vector2f& MousePos, const float& dt);
		void render(RenderTarget& target);
	};
}

#endif // !BUTTON_H