#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font):Menufont(font)
{
	this->BackGround.setSize(Vector2f(static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y))
	);
	this->BackGround.setFillColor(Color(20, 20, 20, 100));
	this->container.setSize(Vector2f(static_cast<float>(window.getSize().x)/4,
		static_cast<float>(window.getSize().y)- 120.f)
	);
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		60.f);
	this->MenuText.setFont(Menufont);
	this->MenuText.setFillColor(Color(255, 255, 255, 200));
	this->MenuText.setCharacterSize(60);
	this->MenuText.setString("PAUSED");
	this->MenuText.setPosition(this->container.getPosition().x+55, this->container.getPosition().y+100);
}

PauseMenu::~PauseMenu()
{
	auto it = this->PauseMenu_Btn.begin();

	for (it = this->PauseMenu_Btn.begin(); it != this->PauseMenu_Btn.end(); it++)
	{
		delete it->second;
	}
}

map<string, Button*>& PauseMenu::GetButtons()
{
	return this->PauseMenu_Btn;
}

const bool PauseMenu::isButtonPressed(const string& key) 
{
	return this->PauseMenu_Btn[key]->isPressed();
}

void PauseMenu::AddButtons(const string& key, const float& y, const string& name)
{
	float width = 150, height = 50;
	float x = this->container.getPosition().x + this->container.getSize().x /2.f - width/2;
	this->PauseMenu_Btn[key] = new Button(x, y, width, height,
		&this->Menufont, name, 30, Color(100, 100, 200, 50),
		Color(50, 150, 200, 125),
		Color(30, 30, 70, 180), Color(100, 100, 200, 150),
		Color(50, 150, 200, 185),
		Color(30, 30, 70, 230));
}

void PauseMenu::update(const Vector2f& mousePosition)
{
	for (auto &i : PauseMenu_Btn)
	{
		i.second->update(mousePosition);
	}
}

void PauseMenu::render(RenderTarget& target)
{
	target.draw(this->BackGround);
	target.draw(this->container);
	for (auto& it : this->PauseMenu_Btn)
	{
		it.second->render(target);
	}
	target.draw(this->MenuText);
}
