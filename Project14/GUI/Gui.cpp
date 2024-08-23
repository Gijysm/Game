#include "..//stdafx.h"
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

void gui::Button::update(const Vector2i& MousePos)
{
	this->Button_State = BTN_IDLE;
	if (this->Shape.getGlobalBounds().contains(static_cast<Vector2f>(MousePos)))
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
void gui::DropDownList::update(const Vector2i& MousePos, const float& dt)
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

gui::TextureSelector::TextureSelector(const float& x, const float& y, 
	const float& width, const float& height, 
	const float& gridSize, 
	const Texture* texture_sheet, Font& font,
	const string& str, VideoMode vm)
	: active(active), gridSize(gridSize), Keytime(0), KeytimeMax(5)
{
	this->hiden = false;
	this->offset = gridSize;
	this->bounds.setSize(Vector2f(width, height));
	this->bounds.setPosition(x, y);
	this->bounds.setFillColor(Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(Color(255, 255, 255, 200));
	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));

	}
	if (this->sheet.getGlobalBounds().height> this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));

	}
	this->selector.setPosition(x, y);
	this->selector.setSize(Vector2f(this->gridSize, this->gridSize));
	this->selector.setFillColor(Color::Transparent);
	this->selector.setOutlineThickness(1);
	this->selector.setOutlineColor(Color::Red);

	this->TextureRect.width = static_cast<int>(gridSize);
	this->TextureRect.height = static_cast<int>(gridSize);
	this->Hide_Button = new Button(gui::p2pX(85, vm), gui::p2pY(85, vm), gui::p2pX(12, vm), gui::p2pY(7, vm),
		&font, str, gui::CharacterSize(vm), Color(100, 100, 200, 50),
		Color(50, 150, 200, 125),
		Color(30, 30, 70, 180), Color(100, 100, 200, 150),
		Color(50, 150, 200, 185),
		Color(30, 30, 70, 230));
}

gui::TextureSelector::~TextureSelector()
{
	delete this->Hide_Button;
}

const bool& gui::TextureSelector::GetActive() const
{
	return active;
}

const IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->TextureRect;
}

const bool gui::TextureSelector::GetKeyTime()
{
	if (this->Keytime >= this->KeytimeMax)
	{
		this->Keytime = 0;
		return true;
	}
	return false;
}

void gui::TextureSelector::UpdateKeyTime(const float& dt)
{
	if (this->Keytime < this->KeytimeMax)
	{
		this->Keytime += 10 * dt;
	}
}

void gui::TextureSelector::update(const Vector2i& MousePosWindow, const float& dt)
{
	UpdateKeyTime(dt);
	this->Hide_Button->update(MousePosWindow);
	if (this->Hide_Button->isPressed() && this->GetKeyTime())
	{
		if(this->hiden)
		{
			this->hiden = false;
		}
		else
		{
			this->hiden = true;
		}
	}
	if(!this->hiden)
	{
		this->active = false;
		if (this->bounds.getGlobalBounds().contains(static_cast<Vector2f>(MousePosWindow)))
		{
			this->active = true;
			this->mousePosGrid.x = ((MousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(gridSize));
			this->mousePosGrid.y = ((MousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(gridSize));
			this->selector.setPosition(this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);
			this->TextureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
			this->TextureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);

		}
	}
}


void gui::TextureSelector::render(RenderTarget& target)
{
	this->Hide_Button->render(target);
	if(!this->hiden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		if (this->active)
		{
			target.draw(this->selector);
		}
	}
}

gui::ProgressBar::ProgressBar(float dx, float dy, float width, float height, int XpositionText,
	int YpositionText,  int MaxHp, VideoMode vm, Font* font,
		Color colorText, Color colorLineer): maxValue(MaxHp),
x(gui::p2pX(dx, vm)), y(gui::p2pY(dy, vm)),screenWidth(gui::p2pX( width, vm)),
screenHeight(gui::p2pY(height, vm))
{

	this->maxWidth = screenHeight * 0.15;
	// Player bars    
	if(font)
	{
		this->text.setFont(*font);
		this->text.setCharacterSize(static_cast<unsigned int>(screenHeight * 0.0269f));
		this->text.setFillColor(colorText);
		this->text.setPosition(XpositionText, YpositionText);
	}
	this->lineer.setSize(Vector2f(screenWidth * 0.125f, screenHeight * 0.013f));
	this->lineer.setFillColor(colorLineer);
	this->lineer.setOutlineThickness(1.f);
	this->lineer.setOutlineColor(Color::White);
	this->lineer.setPosition(dx, dy);

}

void gui::ProgressBar::LoadBack(float dx, float dy, float width, float height, VideoMode vm)
{
	this->Back.setSize(Vector2f(screenWidth * 0.2f, screenHeight * 0.03f));
	this->Back.setFillColor(Color(50, 50, 50, 200));
	this->Back.setPosition(gui::p2pX(1.5, vm), gui::p2pY(1.5,vm));
}

gui::ProgressBar::~ProgressBar()
{
}

const Vector2f gui::ProgressBar::GetPositionB() const
{
	return this->lineer.getPosition();
}

const unsigned int gui::ProgressBar::GetSizeT()
{
	return this->text.getCharacterSize();
}

const Vector2f gui::ProgressBar::GetPositionBB() const
{
	return this->Back.getPosition();
}

const Vector2f gui::ProgressBar::GetPositionT()const
{
	return this->text.getPosition();
}

void gui::ProgressBar::SetPosition(const float& x, const float& y)
{
	this->lineer.setPosition(x, y);
}

void gui::ProgressBar::Update(const int& current_value)
{
	float percent = static_cast<float>(current_value) / this->maxValue;
	this->lineer.setSize(Vector2f(static_cast<float>(floor(this->maxWidth * percent)),
		this->lineer.getSize().y));
	this->ProgressBarString = std::to_string(current_value) + "/" +
		std::to_string(this->maxValue);
	this->text.setString(this->ProgressBarString);
}

void gui::ProgressBar::Render(RenderTarget& target)
{
		target.draw(this->Back);
	target.draw(this->lineer);
	target.draw(this->text);
}
void gui::ProgressBar::RenderBack(RenderTarget& target)
{
	target.draw(this->Back);
}

const float gui::p2pX(const float perc, VideoMode vm)
{
	return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

const float gui::p2pY(const float perc, VideoMode vm)
{
	return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

const unsigned gui::CharacterSize(VideoMode vm)
{
	return static_cast<unsigned>((vm.width + vm.height) / 60.f);
}
