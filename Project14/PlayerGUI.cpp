#include "PlayerGUI.h"

void PlayerGUI::InitFont()
{
	this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf");
}

void PlayerGUI::InitPlayerBars()
{
	// Player bars	
	this->playerBarBack.setSize(Vector2f(300.f, 25.f));
	this->playerBarBack.setFillColor(Color(50, 50, 50, 200));
	this->playerBarBack.setPosition(20.f, 20.f);
	this->playerHpBar.setSize(Vector2f(187.5f, 12.4f));
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(this->playerBarBack.getPosition());
	this->playerManaBar.setSize(Vector2f(187.5f, 13.f));
	this->playerManaBar.setFillColor(Color(99, 62, 213));
	this->playerManaBar.setPosition(this->playerBarBack.getPosition().x, this->playerBarBack.getPosition().y + 12.f);
	this->playerStaminBar.setSize(Vector2f(56.25f, 6.f));
	this->playerStaminBar.setFillColor(Color(20, 255, 20));
	this->playerStaminBar.setPosition(this->player->getPosition().x, this->player->getPosition().y - 90.f);
	this->playerExpBar.setSize(Vector2f(-125, 12.4));
	this->playerExpBar.setFillColor(Color(255, 223, 0, 200));
	this->playerExpBar.setPosition(this->player->getPosition().x - 10, this->player->getPosition().y + 33);
	// Text
	this->HpText.setFont(this->font);
	this->HpText.setCharacterSize(27);
	this->HpText.setFillColor(Color::Red);
	this->HpText.setPosition(210, 23);
	this->ManaText.setFont(this->font);
	this->ManaText.setCharacterSize(27);
	this->ManaText.setFillColor(Color(99, 62, 213));
	this->ManaText.setPosition(210 + 54, 23);
	this->ExpText.setFont(this->font);
	this->ExpText.setCharacterSize(27);
	this->ExpText.setFillColor(Color::Yellow);
	this->ExpText.setPosition(210 + 54 + 54, 23);
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->InitFont();
	this->InitPlayerBars();
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

void PlayerGUI::UpdateManaBar()
{
	float ManaPercent = static_cast<float>(this->player->getAtributeComponent()->mana) / this->player->getAtributeComponent()->manaMax;
	this->playerManaBar.setSize(Vector2f(187.5f * ManaPercent, this->playerManaBar.getSize().y));
	this->ManaBarString = std::to_string(this->player->getAtributeComponent()->mana) + "/" +
		std::to_string(this->player->getAtributeComponent()->manaMax);
	this->ManaText.setString(this->ManaBarString);
}

void PlayerGUI::UpdateExpBar()
{
	float ExpPercent = static_cast<float>(this->player->getAtributeComponent()->exp) / this->player->getAtributeComponent()->expnext;
	this->playerExpBar.setSize(Vector2f(11, -(125 * ExpPercent)));
	this->UpdateColor(this->player->getAtributeComponent()->exp, 10, this->playerExpBar);
	this->ExpBarString = std::to_string(this->player->getAtributeComponent()->exp) + "/" +
		std::to_string(this->player->getAtributeComponent()->expnext);
	this->ExpText.setString(this->ExpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->UpdateHpBar();
	this->UpdateManaBar();
	this->UpdateExpBar();
}

void PlayerGUI::UpdateColor(int Exp, int zmina, RectangleShape& shape)
{
	// Використання лічильника для обмеження частоти зміни кольору
	this->colorChangeCounter++;
	bool colorChange = false;

	if (this->colorChangeCounter >= 60) // Зміна кольору кожні 60 кадрів
	{
		if (Exp % zmina == 0) // Перевірка умови зміни кольору
		{
			shape.setFillColor(Color(rand() % 255, rand() % 255, rand() % 255, 150));
		}

		this->colorChangeCounter = 0; // Скидання лічильника після зміни кольору
	}
}

void PlayerGUI::Render(RenderTarget& target)
{
	this->RenderHpBar(target);
	this->RenderManaBar(target);
	this->RenderExpBar(target);
}

void PlayerGUI::RenderHpBar(RenderTarget& target)
{
	target.draw(this->playerBarBack);
	target.draw(this->playerHpBar);
	target.draw(this->playerStaminBar);
	target.draw(this->HpText);
}

void PlayerGUI::RenderManaBar(RenderTarget& target)
{
	target.draw(this->playerManaBar);
	target.draw(this->ManaText);
}

void PlayerGUI::RenderExpBar(RenderTarget& target)
{
		target.draw(this->playerExpBar);
	target.draw(this->ExpText);
}
