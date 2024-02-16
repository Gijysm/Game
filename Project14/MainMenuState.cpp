#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
	:State(window, supportedKey, states)
{
	this->InitVariables();
	this->InitBackGround();
	this->InitFont();
	this->InitKeyBinds();
	this->InitButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = this->MainMenuState_Btn.begin();

	for (it = this->MainMenuState_Btn.begin(); it != this->MainMenuState_Btn.end(); it++)
	{
		delete it->second;
	}
}

void MainMenuState::InitVariables()
{
}

void MainMenuState::InitBackGround()
{
	this->BackGround.setSize(
		Vector2f(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);
	if (!this->BackGroundTexture.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Background\\20240122151658_1.jpg"))
	{
		throw "FAILED LOAD IMAGE";
	}
	this->BackGround.setTexture(&this->BackGroundTexture);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void MainMenuState::InitButtons()
{
	this->MainMenuState_Btn["Button_NewGame"] = new Button(100, 100, 150, 50,
		&this->font, "New Game", sf::Color(70, 70, 70, 50),
		sf::Color(150, 170, 120, 255),
		sf::Color(20, 20, 90, 230));

	this->MainMenuState_Btn["Button_Settings"] = new Button(100, 200, 150, 50,
		&this->font, "Settings", sf::Color(70, 70, 70, 50),
		sf::Color(150, 170, 120, 255),
		sf::Color(20, 20, 90, 230));

	this->MainMenuState_Btn["Button_Edit"] = new Button(100, 350, 150, 50,
		&this->font, "Edit", sf::Color(70, 70, 70, 50),
		sf::Color(150, 170, 120, 255),
		sf::Color(20, 20, 90, 230));
	this->MainMenuState_Btn["Button_Exit"] = new Button(100, 500, 150, 50,
		&this->font, "Exit", sf::Color(70, 70, 70, 50),
		sf::Color(150, 170, 120, 255),
		sf::Color(20, 20, 90, 230));
}



void MainMenuState::InitKeyBinds()
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

void MainMenuState::EndState()
{
	cout << "Ending_State" << "\n";
}

void MainMenuState::Update_Input(const float& dt)
{
	this->CheckForEnd();

}

void MainMenuState::updateButton()
{

	for (auto &it : this->MainMenuState_Btn)
	{
		it.second->update(this->MousePosView);
	}

	if (this->MainMenuState_Btn["Button_NewGame"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKey, this->states));
	}

	if (this->MainMenuState_Btn["Button_Exit"]->isPressed())
	{
		this->Wants_end = true;
	}
}

void MainMenuState::renderButton(RenderTarget* target)
{

	for (auto& it : this->MainMenuState_Btn)
	{
		it.second->render(target);;
	}
}

void MainMenuState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->Update_Input(dt);
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
	this->updateButton();
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->BackGround);
	this->renderButton(target);

	/*Text MouseText;
	MouseText.setPosition(MousePosView + Vector2f(15, 10));
	MouseText.setFont(font);
	MouseText.setCharacterSize(15);
	stringstream ss;
	ss << MousePosView.x << " " << MousePosView.y;
	MouseText.setString(ss.str());
	target->draw(MouseText);*/
}
