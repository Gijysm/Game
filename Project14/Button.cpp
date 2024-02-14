#include "Button.h"

Button::Button(float x, float y, float Width, float height, 
	Font* font, string text, 
	Color idle_Color, Color hower_Color, Color active_Color)
	:Idle_Color(idle_Color), Hower_Color(hower_Color),
	Active_Color(active_Color)
{
	this->Shape.setPosition(Vector2f(x, y));
	this->Shape.setSize(Vector2f(Width, height));

	this->font = font;
	this->Text.setFont(*this->font);
	this->Text.setString(text);
	this->Text.setFillColor(Color::Magenta);
	this->Text.setCharacterSize(15);

	this->Text.setPosition(
		this->Shape.getPosition().x / 2.f - this->Text.getGlobalBounds().width / 2.f,
		this->Shape.getPosition().y / 2.f - this->Text.getGlobalBounds().height / 2.f
	);
	this->Shape.setFillColor(this->Idle_Color);
}

void Button::update(const Vector2f MousePos)
{
}

void Button::render(RenderTarget* target)
{
	target->draw(this->Shape);
}
