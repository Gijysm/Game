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
	this->HpText.setFont(this->font);
	this->HpText.setCharacterSize(27);
	this->HpText.setFillColor(Color::Red);
	this->HpText.setPosition(210, 23);

	this->playerHpBar.setSize(Vector2f(187.5f, 12.4f));
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(this->playerHpBarBack.getPosition());
	this->playerManaBar.setSize(Vector2f(187.5f, 13.f));
	this->playerManaBar.setFillColor(Color(99, 62, 213));
	this->playerManaBar.setPosition(this->playerHpBarBack.getPosition().x, this->playerHpBarBack.getPosition().y + 12.f);
	this->playerStaminBar.setSize(Vector2f(56.25f, 6.f));
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
	// Використання плаваючої точки для обчислення hpPercent
	float hpPercent = static_cast<float>(this->player->getAtributeComponent()->hp) / this->player->getAtributeComponent()->hpMax;
	this->playerHpBar.setSize(Vector2f(187.5f * hpPercent, this->playerHpBar.getSize().y));
	this->hpBarString = std::to_string(this->player->getAtributeComponent()->hp) + "/" +
		std::to_string(this->player->getAtributeComponent()->hpMax);
	this->HpText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->UpdateHpBar();
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
	target.draw(this->HpText);
}
