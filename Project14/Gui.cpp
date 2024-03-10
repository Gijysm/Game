#include "Gui.h"


gui::Button::Button(float x, float y, float Width, float height,
	Font* font, string text, int Character_size,
	Color Text_idle_Color, Color Text_hower_Color, Color Text_active_Color,
	Color idle_Color, Color hower_Color, Color active_Color, 
	Color OutLine_idle_Color, Color OutLine_hower_Color,
	Color OutLine_active_Color,
	short unsigned id)
{
	this->id = id;
	this->Shape.setPosition(Vector2f(x, y));
	this->Shape.setSize(Vector2f(Width, height));
	this->Shape.setFillColor(idle_Color);
	this->Shape.setOutlineThickness(1.f);
	this->Shape.setOutlineColor(OutLine_idle_Color);

	this->Button_State = BTN_IDLE;

	this->font = font;
	this->Text.setFont(*this->font);
	this->Text.setString(text);
	this->Text.setFillColor(Text_idle_Color);
	this->Text.setCharacterSize(Character_size);

	this->Text.setPosition(
		this->Shape.getPosition().x + (this->Shape.getGlobalBounds().width / 2.f) - this->Text.getGlobalBounds().width / 2.f,
		this->Shape.getPosition().y + (this->Shape.getGlobalBounds().height / 2.f) - this->Text.getGlobalBounds().height / 2.f
	);

	this->Text_idle_Color = Text_idle_Color;
	this->Text_hower_Color = Text_hower_Color;
	this->Text_active_Color = Text_active_Color;

	this->Idle_Color = idle_Color;
	this->Hower_Color = hower_Color;
	this->Active_Color = active_Color;

	this->OutLine_Idle_Color = OutLine_idle_Color;
	this->OutLine_Hower_Color = OutLine_hower_Color;
	this->OutLine_Active_Color = OutLine_active_Color;

	this->Shape.setFillColor(this->Idle_Color);
}

gui::Button::~Button()
{
}

const bool gui::Button::isPressed() const
{
	if (this->Button_State == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

const string gui::Button::getText() const
{
	return this->Text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

void gui::Button::setText(const string text)
{
	this->Text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::update(const Vector2f& MousePos)
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
		this->Text.setFillColor(Text_idle_Color);
		this->Shape.setOutlineColor(this->OutLine_Idle_Color);
		break;
	case BTN_HOWER:
		this->Shape.setFillColor(Hower_Color);
		this->Text.setFillColor(Text_hower_Color);
		this->Shape.setOutlineColor(this->OutLine_Hower_Color);
		break;
	case BTN_ACTIVE:
		this->Shape.setFillColor(Active_Color);
		this->Text.setFillColor(Text_active_Color);
		this->Shape.setOutlineColor(this->OutLine_Active_Color);
		break;
	default:
		this->Shape.setFillColor(Color::Red);
		this->Text.setFillColor(Color::Red);
		this->Shape.setOutlineColor(Color::Transparent);
	}
}

void gui::Button::render(RenderTarget& target)
{
	target.draw(this->Shape);
	target.draw(this->Text);
}

gui::DropDownList::DropDownList(float x, float y, float width, float height, Font& font, string list[],
	unsigned NOEllements, unsigned default_index)
	: font(font), showlist(false), KeytimeMax(1), Keytime(0)
{	
	this->activeEllement = new Button(x, y, width, height,
		&this->font, list[default_index], 30, 
		Color(255, 255, 255, 150),Color(255, 255, 255, 255),Color(30, 30, 70, 180),
		Color(100, 100, 200, 200),Color(50, 150, 200, 200),Color(30, 30, 70, 200),
		Color(255, 255, 255, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50));
	for(size_t i = 0; i < NOEllements; i++)
	{
		this->list.push_back(new gui::Button(x, y + ((i + 1) * height), width, height,
			&this->font, list[i], 30,
			Color(255, 255, 255, 150),Color(255, 255, 255, 255),Color(30, 30, 70, 180), 
			Color(100, 100, 200, 200),Color(50, 150, 200, 200),Color(30, 30, 70, 200), 
			Color(255, 255, 255, 0), Color(255, 255, 255, 5), Color(20, 20, 20, 0), i));
	}

}

gui::DropDownList::~DropDownList()
{
	delete this->activeEllement;
		for (auto *&i : this->list)
		{
			delete i;
		}
}

void gui::DropDownList::UpdateKeyTime(const float& dt)
{
	if (this->Keytime < this->KeytimeMax)
	{
		this->Keytime += 10 * dt;
	}
}

const bool gui::DropDownList::GetKeyTime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0;
		return true;
	}
	return false;
}

const unsigned short& gui::DropDownList::getActiveEllementId() const
{
	return this->activeEllement->getId();
}


//DropDown List
void gui::DropDownList::update(const Vector2f& MousePos, const float& dt)
{
	this->UpdateKeyTime(dt);
	this->activeEllement->update(MousePos);
	if (this->activeEllement->isPressed() && this->GetKeyTime())
	{
		if (this->showlist)
		{
			this->showlist = false;
		}
		else
		{
			this->showlist = true;
		}
	}
	if (this->showlist)
	{
		for (auto& i : this->list)
		{
			i->update(MousePos);
		if(i->isPressed() && this->GetKeyTime())
		{
			this->showlist = false;
			this->activeEllement->setText(i->getText());
			this->activeEllement->setId(i->getId());
		}
		}
	}
}

void gui::DropDownList::render(RenderTarget& target)
{
	this->activeEllement->render(target);
	if(showlist)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}

}
