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

void PauseMenu::update()
{
}

void PauseMenu::render(RenderTarget& target)
{
	target.draw(this->BackGround);
	target.draw(this->container);
	for (auto& it : this->PauseMenu_Btn)
	{
		it.second->render(&target);
	}
	target.draw(this->MenuText);
}
