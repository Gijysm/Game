#include "SettingsState.h"

SettingsState::SettingsState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
	: State(window, supportedKey, states)
{
	this->InitVariables();
	this->InitBackGround();
	this->InitFont();
	this->InitKeyBinds();
	this->InitGui();
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
		it.second->update(this->MousePosView);
	}

	if (this->Buttons["Button_Exit"]->isPressed())
	{
		this->EndState();
	}
	for (auto& it : this->dropdownList)
	{
		it.second->update(this->MousePosView,dt);
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

	/*Text MouseText;
	MouseText.setPosition(MousePosView + Vector2f(15, 10));
	MouseText.setFont(font);
	MouseText.setCharacterSize(15);
	stringstream ss;
	ss << MousePosView.x << " " << MousePosView.y;
	MouseText.setString(ss.str());
	target->draw(MouseText);*/
}

void SettingsState::InitVariables()
{
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

	this->Buttons["Button_Exit"] = new gui::Button(560, 600, 150, 50,
		&this->font, "Back", 30, Color(255, 0, 0, 50),
		Color(255, 100, 100, 125),
		Color(150, 0, 0, 180), Color(255, 0, 0, 150),
		Color(255, 100, 100, 185),
		Color(150, 0, 0, 230));
	string li[] = { "1920x1080","800x600","640x480" };
	this->dropdownList["RESOLUTION"] = new gui::DropDownList(540, 200, 200, 50, font, li, 3);
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