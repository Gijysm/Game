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
	auto it = this->Buttons.begin();

	for (it = this->Buttons.begin(); it != this->Buttons.end(); it++)
	{
		delete it->second;
	}

	auto it2 = this->dropdownList.begin();

	for (it2 = this->dropdownList.begin(); it2 != this->dropdownList.end(); it2++)
	{
		delete it2->second;
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

	for (auto& it : this->Buttons)
	{
		it.second->update(this->MousePosWindow);
	}

	if (this->Buttons["Button_Exit"]->isPressed())
	{
		this->EndState();
	}
	if (this->Buttons["APPLY"]->isPressed())
	{
		this->Statedata->GFXSettings->resolution = this->modes[this->dropdownList["RESOLUTION"]->getActiveEllementId()];
		this->window->create(this->Statedata->GFXSettings->resolution, this->Statedata->GFXSettings->title, Style::Default);
	}
	for (auto& it : this->dropdownList)
	{
		it.second->update(this->MousePosWindow,dt);
	}

}

void SettingsState::renderGui(RenderTarget& target)
{

	for (auto& it : this->Buttons)
	{
		it.second->render(target);
	}
	for (auto& it : this->dropdownList)
	{
		it.second->render(target);
	}
}

void SettingsState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->updateInput(dt);
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
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
}

void SettingsState::InitBackGround()
{
	//this->BackGround.setSize(
	//	Vector2f(
	//		static_cast<float>(this->window->getSize().x),
	//		static_cast<float>(this->window->getSize().y)
	//	)
	//);
	//if (!this->BackGroundTexture.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Background\\20240122151658_1.jpg"))
	//{
	//	throw "FAILED LOAD IMAGE";
	//}
	//this->BackGround.setTexture(&this->BackGroundTexture);
}

void SettingsState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void SettingsState::InitGui()
{

	this->Buttons["Button_Exit"] = new gui::Button(960, 600, 150, 50,
		&this->font, "Back", 30, Color(255, 0, 0, 50),
		Color(255, 100, 100, 125),
		Color(150, 0, 0, 180), Color(255, 0, 0, 150),
		Color(255, 100, 100, 185),
		Color(150, 0, 0, 230));
	this->Buttons["APPLY"] = new gui::Button(160, 600, 150, 50,
		&this->font, "Apply", 30, Color(255, 0, 0, 50),
		Color(255, 100, 100, 125),
		Color(150, 0, 0, 180), Color(255, 0, 0, 150),
		Color(255, 100, 100, 185),
		Color(150, 0, 0, 230));
	vector<string> modes_str;
	for (auto& i : modes)
	{
		modes_str.push_back(to_string(i.width) + 'X' + to_string(i.height));
	}
	this->dropdownList["RESOLUTION"] = new gui::DropDownList(540, 100, 200, 50, font, modes_str.data(), modes_str.size());
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

	this->optionsText.setPosition(Vector2f(100, 100));

	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(Color(255, 255, 255, 200));;
	this->optionsText.setString("Resolution\nFullsreen\nVsyc\nAntialising\n");
}
