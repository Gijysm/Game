#include "..//stdafx.h"
#include "PlayerGUI.h"
void PlayerGUI::InitFont()
{
    this->font.loadFromFile("..\\Font\\DungeonFont.ttf");
}

void PlayerGUI::InitPlayerBars()
{
    VideoMode vm = VideoMode::getDesktopMode();
    int width = 3;
    int height = 116;
    float screenWidth = gui::p2pX( width, vm);
    float screenHeight = gui::p2pY( height, vm);

    // Player bars    
    this->hpBar = new gui::ProgressBar(gui::p2pX(1.65, vm),
        gui::p2pY(1.95, vm),width, height,
        gui::p2pX(11.5, vm), gui::p2pY(2.25, vm),
        this->player->getAtributeComponent()->hpMax, vm, &font, Color::Red,Color::Red);
    this->hpBar->LoadBack(0,0,width, height,vm);
    
    this->ManaBar = new gui::ProgressBar(gui::p2pX(1.65, vm),
        gui::p2pY(3.25, vm),width, height,
    this->hpBar->GetPositionT().x + screenWidth, this->hpBar->GetPositionT().y,
    this->player->getAtributeComponent()->manaMax, vm, &font, Color::Blue,Color::Blue);
    

    this->StaminaBar = new gui::ProgressBar(this->player->getPosition().x - gui::p2pX(7.5, vm),
        this->player->getPosition().y - gui::p2pY(6, vm),
        this->player->GetSize().x / 2,  (screenHeight * 0.06f) ,gui::p2pX(11.5, vm), gui::p2pY(2.25, vm),
        this->player->getAtributeComponent()->hpMax, vm, &font, Color::Green,Color::Green);

    this->ExpBar = new gui::ProgressBar(this->player->getPosition().x - gui::p2pX(8, vm), this->player->getPosition().y + gui::p2pY(7.5, vm),
        -gui::p2pX(screenWidth * 0.083f, vm), gui::p2pY(screenHeight * 0.015f, vm) ,gui::p2pX(11.5, vm), gui::p2pY(2.25, vm),
        this->player->getAtributeComponent()->hpMax, vm, &font, Color::Yellow,Color(255, 223, 0, 200));

    


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
    this->ManaBar->Update(this->player->getAtributeComponent()->mana);

}

void PlayerGUI::UpdateExpBar()
{
    /*float ExpPercent = static_cast<float>(this->player->getAtributeComponent()->exp) / this->player->getAtributeComponent()->expnext;
    this->playerExpBar.setSize(Vector2f(11, -(this->player->GetSize().y * ExpPercent)));
    this->UpdateColor(this->player->getAtributeComponent()->exp, 10, this->playerExpBar);
    this->ExpBarString = std::to_string(this->player->getAtributeComponent()->exp) + "/" +
        std::to_string(this->player->getAtributeComponent()->expnext);
    this->ExpText.setString(this->ExpBarString);
    this->LevelText.setString(std::to_string(this->player->getAtributeComponent()->level));
    this->UpdateColor(this->player->getAtributeComponent()->level, 5, this->LevelText);*/
}

void PlayerGUI::UpdateDynamicalElliments()
{
    this->ExpBar->SetPosition(this->player->getPosition().x - 15, this->player->getPosition().y + 55);
    this->StaminaBar->SetPosition(this->player->getPosition().x, this->player->getPosition().y - 12);
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
    this->StaminaBar->Render(target);
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
    this->ManaBar->Render(target);
}

void PlayerGUI::RenderExpBar(RenderTarget& target)
{
    this->ExpBar->Render(target);
    target.draw(this->playerStaminBar);
    target.draw(this->LevelText);
}
