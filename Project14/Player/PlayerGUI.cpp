#include "..//stdafx.h"
#include "PlayerGUI.h"
void PlayerGUI::InitFont()
{
    this->font.loadFromFile("..\\Font\\DungeonFont.ttf");
}

void PlayerGUI::InitPlayerBars()
{
    vm = VideoMode::getDesktopMode();
    int width = gui::p2pX( 25, vm);
    int height = gui::p2pY( 2, vm);
    float screenWidth = gui::p2pX( width, vm);
    float screenHeight = gui::p2pY( height, vm);

    // Player bars    
    this->hpBar = new gui::ProgressBar(gui::p2pX(0, vm),
        gui::p2pY(2, vm),width, height,
         gui::CharacterSize(vm) ,gui::p2pX(13.5, vm), gui::p2pY(2.25, vm),
        this->player->getAtributeComponent()->hpMax, vm, &font, Color::Red,Color::Red);
    this->hpBar->LoadBack(0,0,width, height);
    
    this->ManaBar = new gui::ProgressBar(gui::p2pX(0, vm),
        gui::p2pY(4, vm),width, height,
     gui::CharacterSize(vm) ,this->hpBar->GetPositionT().x + (this->hpBar->GetSizeText() * 2), this->hpBar->GetPositionT().y,
    this->player->getAtributeComponent()->manaMax, vm, &font, Color::Blue,Color::Blue);
    
        this->StaminaBar = new gui::ProgressBar(this->player->getPosition().x - gui::p2pX(7.5, vm),
           this->player->getPosition().y - gui::p2pY(6, vm),
           this->player->GetSize().x,  (screenHeight * 0.03f), gui::CharacterSize(vm)
           ,gui::p2pX(11.5, vm), gui::p2pY(2.25, vm),
           this->player->getAtributeComponent()->hpMax, vm, &font, Color::Green,Color::Green);

        this->ExpBar = new gui::ProgressBar(this->player->getPosition().x - gui::p2pX(2, vm), this->player->getPosition().y - gui::p2pY(9.5, vm),
            -gui::p2pX(screenWidth * 0.0073f, vm),
            this->player->GetSize().y * 2 , gui::CharacterSize(vm) ,
            this->ManaBar->GetPositionT().x + (this->ManaBar->GetSizeText() * 2), gui::p2pY(2.25, vm),
            this->player->getAtributeComponent()->expnext, vm, &font, Color::Yellow,Color(255, 223, 0, 200));

    // Text
    
    this->LevelText.setFont(this->font);
    this->LevelText.setString(to_string(this->player->getAtributeComponent()->level));
    this->LevelText.setCharacterSize(gui::CharacterSize(vm)/2);
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
this->hpBar->Update(this->player->getAtributeComponent()->hp, gui::F_ont::Width);
}

void PlayerGUI::UpdateManaBar()
{
    this->ManaBar->Update(this->player->getAtributeComponent()->mana, gui::F_ont::Width);

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
    this->ExpBar->Update(this->player->getAtributeComponent()->exp,this->player->getAtributeComponent()->expnext, gui::F_ont::Height);
}

void PlayerGUI::UpdateDynamicalElliments()
{
    this->ExpBar->SetPositionLineer(this->player->getPosition().x - gui::p2pX(1.15, vm), this->player->getPosition().y  + gui::p2pY(5.5, vm));
    this->StaminaBar->SetPositionLineer(this->player->getPosition().x, this->player->getPosition().y - gui::p2pY(2.5, vm));
    this->LevelText.setString(to_string(this->player->getAtributeComponent()->level));
    this->LevelText.setPosition(this->StaminaBar->GetPositionLineer().x + (this->StaminaBar->GetSizeLineer().x / 2.75), this->StaminaBar->GetPositionLineer().y - 30);
}

void PlayerGUI::update(const float& dt)
{
    this->UpdateHpBar();
    this->UpdateManaBar();
    this->UpdateExpBar();


}

void PlayerGUI::UpdateColor(int Exp, int zmina, RectangleShape& shape)
{
    if (Exp % zmina == 0 && !Layerchanged)
    {
        shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256, 150));
        Layerchanged = true; 
    }
    else if (Exp % zmina != 0)
    {
        Layerchanged = false;
    }
}

void PlayerGUI::UpdateColor(int Exp, int zmina, Text& shape)
{
    if (Exp % zmina == 0 && !Textchanged) 
    {
        shape.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
        Textchanged = true; 
    }
    else if (Exp % zmina != 0) 
    {
        Textchanged = false;
    }
}

void PlayerGUI::Render_Dynamical(RenderTarget& target)
{
    target.draw(this->LevelText);
    this->ExpBar->RenderLineer(target);
    this->StaminaBar->Render(target);
}

void PlayerGUI::Render(RenderTarget& target)
{
    this->RenderHpBar(target);
    this->RenderExpBar(target);
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
    this->ExpBar->RenderText(target);
    target.draw(this->playerStaminBar);
}
