#include "stdafx.h"
#include "SettingsState.h"

SettingsState::SettingsState(StateData* state_data)
    : State(state_data)
{
    this->InitVariables();
    this->InitBackGround();
    this->InitFont();
    this->InitKeyBinds();
    this->InitGui();
    this->initText();
}

SettingsState::~SettingsState()
{
    for (auto& button : this->Buttons)
    {
        delete button.second;
    }

    for (auto& dropdown : this->dropdownList)
    {
        delete dropdown.second;
    }
}

void SettingsState::updateInput(const float& dt)
{
    if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))))
    {
        this->EndState();
    }
}

void SettingsState::updateGui(const float& dt)
{
    for (auto& button : this->Buttons)
    {
        button.second->update(this->MousePosWindow);
    }

    if (this->Buttons["Button_Exit"]->isPressed())
    {
        this->EndState();
    }
    if (this->Buttons["APPLY"]->isPressed())
    {
        if (this->Statedata && this->Statedata->GFXSettings)
        {
            int selectedId = this->dropdownList["RESOLUTION"]->getActiveEllementId();
            std::cout << "Selected resolution ID: " << selectedId << std::endl;
            if (selectedId >= 0 && selectedId < this->modes.size())
            {
                this->Statedata->GFXSettings->resolution = this->modes[selectedId];
                this->window->create(this->Statedata->GFXSettings->resolution, this->Statedata->GFXSettings->title, Style::Default);
                vm = this->Statedata->GFXSettings->resolution;
                std::cout << "New resolution: " << vm.width << "x" << vm.height << std::endl;
            }
            else
            {
                std::cerr << "Invalid resolution ID selected." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Statedata or GFXSettings is null." << std::endl;
        }
    }

    for (auto& dropdown : this->dropdownList)
    {
        dropdown.second->update(this->MousePosWindow, dt);
    }
}

void SettingsState::renderGui(RenderTarget& target)
{
    for (auto& button : this->Buttons)
    {
        button.second->render(target);
    }
    for (auto& dropdown : this->dropdownList)
    {
        dropdown.second->render(target);
    }
}

void SettingsState::update(const float& dt)
{
    this->UpdateMousePosition();
    this->updateInput(dt);
    this->updateGui(dt);
}

void SettingsState::render(RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }
    target->draw(this->BackGround);
    this->renderGui(*target);
    target->draw(this->optionsText);

    Text MouseText;
    MouseText.setPosition(MousePosView + Vector2f(15, 10));
    MouseText.setFont(font);
    MouseText.setCharacterSize(15);
    stringstream ss;
    ss << MousePosView.x << " " << MousePosView.y;
    MouseText.setString(ss.str());
    target->draw(MouseText);
}

void SettingsState::InitVariables()
{
    this->modes = VideoMode::getFullscreenModes();
    if (this->modes.empty())
    {
        std::cerr << "Error: No fullscreen modes available." << std::endl;
    }
}

void SettingsState::InitBackGround()
{
    // Background initialization code...
}

void SettingsState::InitFont()
{
    if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
    {
        throw "Error: Could not load font.";
    }
}

void SettingsState::InitGui()
{
    vm = this->Statedata->GFXSettings->resolution;

    this->Buttons["Button_Exit"] = new gui::Button(gui::p2pX(85, vm), gui::p2pY(85, vm),
        gui::p2pX(12, vm), gui::p2pY(7, vm),
        &this->font, "Back", gui::CharacterSize(vm), Color(255, 0, 0, 50),
        Color(255, 100, 100, 125),
        Color(150, 0, 0, 180), Color(255, 0, 0, 150),
        Color(255, 100, 100, 185),
        Color(150, 0, 0, 230));

    this->Buttons["APPLY"] = new gui::Button(gui::p2pX(5, vm), gui::p2pY(85, vm),
        gui::p2pX(12, vm), gui::p2pY(7, vm),
        &this->font, "Apply", gui::CharacterSize(vm), Color(255, 0, 0, 50),
        Color(255, 100, 100, 125),
        Color(150, 0, 0, 180), Color(255, 0, 0, 150),
        Color(255, 100, 100, 185),
        Color(150, 0, 0, 230));

    vector<string> modes_str;
    for (auto& mode : modes)
    {
        modes_str.push_back(to_string(mode.width) + 'X' + to_string(mode.height));
    }
    this->dropdownList["RESOLUTION"] = new gui::DropDownList(gui::p2pX(45, vm), gui::p2pY(13, vm), gui::p2pX(16, vm), gui::p2pY(7, vm), font, modes_str.data(), modes_str.size());
}

void SettingsState::InitKeyBinds()
{
    ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\MainMenuKey_binds.ini");

    if (ifs.is_open())
    {
        string key = "";
        string Key2 = "";

        while (ifs >> key >> Key2)
        {
            this->KeyBinds[key] = this->supportedKey->at(Key2);
        }
    }
    ifs.close();
}

void SettingsState::initText()
{
    this->optionsText.setFont(this->font);
    this->optionsText.setPosition(Vector2f(gui::p2pX(10, vm), gui::p2pY(13, vm)));
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(Color(255, 255, 255, 200));
    this->optionsText.setString("Resolution\nFullscreen\nVsync\nAntialiasing\n");
}
