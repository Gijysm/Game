#include "PlayerGUI.h"

void PlayerGUI::InitFont()
{
    this->font.loadFromFile("..\\Font\\DungeonFont.ttf");
}

void PlayerGUI::InitPlayerBars()
{
    VideoMode vm = VideoMode::getDesktopMode();
    float screenWidth = static_cast<float>(vm.width);
    float screenHeight = static_cast<float>(vm.height);

    // Player bars    
    this->hpBar = new gui::ProgressBar(0,0,125, 116,this->player->getAtributeComponent()->hpMax, vm, &font);
    this->playerManaBar.setSize(Vector2f(screenWidth * 0.125f, screenHeight * 0.016f));
    this->playerManaBar.setFillColor(Color(99, 62, 213));
    this->playerManaBar.setOutlineThickness(1.f);
    this->playerManaBar.setOutlineColor(Color::White);
    this->playerManaBar.setPosition(this->hpBar->GetPositionBB().x, (this->hpBar->GetPositionBB().y * 2));

    this->playerStaminBar.setSize(Vector2f(this->player->GetSize().x, screenHeight * 0.008f));
    this->playerStaminBar.setFillColor(Color(20, 255, 20));
    this->playerStaminBar.setOutlineThickness(1.f);
    this->playerStaminBar.setOutlineColor(Color::White);
    this->playerStaminBar.setPosition(this->player->getPosition().x - gui::p2pX(7.5, vm), this->player->getPosition().y - gui::p2pY(6, vm));

    this->playerExpBar.setSize(Vector2f(-screenWidth * 0.083f, screenHeight * 0.015f));
    this->playerExpBar.setFillColor(Color(255, 223, 0, 200));
    this->playerExpBar.setOutlineThickness(1.f);
    this->playerExpBar.setOutlineColor(Color::White);
    this->playerExpBar.setPosition(this->player->getPosition().x - gui::p2pX(8, vm), this->player->getPosition().y + gui::p2pY(7.5, vm));

    // Text
    
    this->ManaText.setFont(this->font);
    this->ManaText.setCharacterSize(static_cast<unsigned int>(screenHeight * 0.03f));
    this->ManaText.setFillColor(Color(99, 62, 213));
    this->ManaText.setPosition(this->hpBar->GetPositionT().x +60, this->hpBar->GetPositionT().y);

    this->ExpText.setFont(this->font);
    this->ExpText.setCharacterSize(static_cast<unsigned int>(screenHeight * 0.03f));
    this->ExpText.setFillColor(Color::Yellow);
    this->ExpText.setPosition(ManaText.getPosition().x + 45, ManaText.getPosition().y);

    this->LevelText.setFont(this->font);
    this->LevelText.setCharacterSize(static_cast<unsigned int>(screenHeight * 0.03f));
    this->LevelText.setFillColor(Color::White);
    this->LevelText.setPosition(this->playerStaminBar.getPosition().x + 30, this->playerStaminBar.getPosition().y -30);
}

PlayerGUI::PlayerGUI(Player* player)
{
    this->player = player;

    this->InitFont();
    this->InitPlayerBars();
}

PlayerGUI::~PlayerGUI()
{
    delete this->hpBar;
}

void PlayerGUI::UpdateHpBar()
{
this->hpBar->Update(this->player->getAtributeComponent()->hp);
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
    this->playerExpBar.setSize(Vector2f(11, -(this->player->GetSize().y * ExpPercent)));
    this->UpdateColor(this->player->getAtributeComponent()->exp, 10, this->playerExpBar);
    this->ExpBarString = std::to_string(this->player->getAtributeComponent()->exp) + "/" +
        std::to_string(this->player->getAtributeComponent()->expnext);
    this->ExpText.setString(this->ExpBarString);
    this->LevelText.setString(std::to_string(this->player->getAtributeComponent()->level));
    this->UpdateColor(this->player->getAtributeComponent()->level, 5, this->LevelText);
}

void PlayerGUI::UpdateDynamicalElliments()
{
    this->playerExpBar.setPosition(this->player->getPosition().x - 15, this->player->getPosition().y + 55);
    this->playerStaminBar.setPosition(this->player->getPosition().x, this->player->getPosition().y - 12);
    this->LevelText.setPosition(this->playerStaminBar.getPosition().x + (this->playerStaminBar.getSize().x / 2.75), this->playerStaminBar.getPosition().y - 30);
}

void PlayerGUI::update(const float& dt)
{
    this->UpdateHpBar();
    this->UpdateManaBar();
    this->UpdateExpBar();


}

void PlayerGUI::UpdateColor(int Exp, int zmina, RectangleShape& shape)
{
    if (Exp % zmina == 0 && !Layerchanged) // Зміна кольору, якщо Exp кратний zmina і колір ще не змінювався
    {
        shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256, 150));
        Layerchanged = true; // Прапорець встановлюється, щоб уникнути повторної зміни кольору
    }
    else if (Exp % zmina != 0) // Скидання прапорця, коли умова більше не виконується
    {
        Layerchanged = false;
    }
}

void PlayerGUI::UpdateColor(int Exp, int zmina, Text& shape)
{
    if (Exp % zmina == 0 && !Textchanged) // Зміна кольору, якщо Exp кратний zmina і колір ще не змінювався
    {
        shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
        Textchanged = true; // Прапорець встановлюється, щоб уникнути повторної зміни кольору
    }
    else if (Exp % zmina != 0) // Скидання прапорця, коли умова більше не виконується
    {
        Textchanged = false;
    }
}

void PlayerGUI::Render_Dynamical(RenderTarget& target)
{
    this->RenderExpBar(target);
}

void PlayerGUI::Render(RenderTarget& target)
{
    this->RenderHpBar(target);
    this->RenderManaBar(target);
}

void PlayerGUI::RenderHpBar(RenderTarget& target)
{
    this->hpBar->Render(target);
}

void PlayerGUI::RenderManaBar(RenderTarget& target)
{
    target.draw(this->playerManaBar);
    target.draw(this->ManaText);
    target.draw(this->ExpText);
}

void PlayerGUI::RenderExpBar(RenderTarget& target)
{
    target.draw(this->playerExpBar);
    target.draw(this->playerStaminBar);
    target.draw(this->LevelText);
}
