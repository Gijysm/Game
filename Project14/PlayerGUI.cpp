#include "PlayerGUI.h"

void PlayerGUI::InitFont()
{
	this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf");
}

void PlayerGUI::InitPlayerHpBar()
{
	this->playerHpBarBack.setSize(Vector2f(300.f, 25.f));
	this->playerHpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->playerHpBarBack.setPosition(20.f, 20.f);
	this->playerHpBar.setSize(Vector2f(187.5, 12.4));
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(this->playerHpBarBack.getPosition());
	this->playerManaBar.setSize(Vector2f(187.5, 13));
	this->playerManaBar.setFillColor(Color(99,62,213));
	this->playerManaBar.setPosition(this->playerHpBarBack.getPosition().x, this->playerHpBarBack.getPosition().y + 12.f);
	this->playerStaminBar.setSize(Vector2f(56.25, 6));
	this->playerStaminBar.setFillColor(Color(20, 255, 20));
	this->playerStaminBar.setPosition(this->player->getPosition().x, this->player->getPosition().y - 90.f);
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->InitFont();
	this->InitPlayerHpBar();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::UpdateHpBar()
{
}

void PlayerGUI::update(const float& dt)
{
}

void PlayerGUI::Render(RenderTarget& target)
{
	this->RenderHpBar(target);
}

void PlayerGUI::RenderHpBar(RenderTarget& target)
{
	target.draw(this->playerHpBarBack);
	target.draw(this->playerHpBar);
	target.draw(this->playerManaBar);
	target.draw(this->playerStaminBar);
}
