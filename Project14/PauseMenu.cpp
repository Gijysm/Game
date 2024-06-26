#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(VideoMode vm, Font& font):Menufont(font)
{
	this->BackGround.setSize(Vector2f(static_cast<float>(vm.width), 
		static_cast<float>(vm.height))
	);
	this->BackGround.setFillColor(Color(20, 20, 20, 100));
	this->container.setSize(Vector2f(static_cast<float>(vm.width)/4,
		static_cast<float>(vm.height)- 120.f)
	);
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f,
		60.f);
	this->MenuText.setFont(Menufont);
	this->MenuText.setFillColor(Color(255, 255, 255, 200));
	this->MenuText.setCharacterSize(60);
	this->MenuText.setString("PAUSED");
	this->MenuText.setPosition(p2pX(43, vm), p2pY(15,vm));
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

void PauseMenu::AddButtons(const string& key, const float& y, const int CharacterSize, const string& name)
{
	float width = 150, height = 50;
	float x = this->container.getPosition().x + this->container.getSize().x /2.f - width/2;
	this->PauseMenu_Btn[key] = new Button(x, y, width, height,
		&this->Menufont, name, CharacterSize, Color(124, 206, 239, 125),
		Color(50, 150, 200, 250),
		Color(247, 123, 116, 200), Color(30, 190, 253, 150),
		Color(64, 64, 64, 120),
		Color(64, 64, 64, 72));
}

void PauseMenu::update(const Vector2i& mousePosition)
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
