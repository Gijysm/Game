#include "Button.h"

Button::Button(float x, float y, float Width, float height, 
	Font* font, string text, 
	Color idle_Color, Color hower_Color, Color active_Color)
{
	this->Shape.setPosition(Vector2f(x, y));
	this->Shape.setSize(Vector2f(Width, height));

	this->Button_State = BTN_IDLE;

	this->font = font;
	this->Text.setFont(*this->font);
	this->Text.setString(text);
	this->Text.setFillColor(Color::Magenta);
	this->Text.setCharacterSize(32);
	this->Idle_Color = idle_Color;
	this->Hower_Color = hower_Color;
	this->Active_Color = active_Color;

	this->Text.setPosition(
		this->Shape.getPosition().x + (this->Shape.getGlobalBounds().width / 2.f) - this->Text.getGlobalBounds().width / 2.f,
		this->Shape.getPosition().y + (this->Shape.getGlobalBounds().height / 2.f) - this->Text.getGlobalBounds().height / 2.f
	);
	this->Shape.setFillColor(this->Idle_Color);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->Button_State == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

void Button::update(const Vector2f MousePos)
{
	this->Button_State = BTN_IDLE;
	if (this->Shape.getGlobalBounds().contains(MousePos))
	{
		this->Button_State = BTN_HOWER;
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			this->Button_State = BTN_ACTIVE;
		}
	}
	switch (this->Button_State)
	{
	case BTN_IDLE:
		this->Shape.setFillColor(Idle_Color);
		break;
	case BTN_HOWER:
		this->Shape.setFillColor(Hower_Color);
		break;
	case BTN_ACTIVE:
		this->Shape.setFillColor(Active_Color);
		break;
	default:
		this->Shape.setFillColor(Color::Red);
	}
}

void Button::render(RenderTarget* target)
{
	target->draw(this->Shape);
	target->draw(this->Text);
}
