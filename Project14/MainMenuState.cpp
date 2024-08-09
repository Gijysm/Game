#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"


void MainMenuState::InitVariables()
{
}

void MainMenuState::InitBackGround()
{

	if (!this->BackGroundTexture.loadFromFile("..\\Background\\20240122151658_1.jpg"))
	{
		throw "FAILED LOAD IMAGE";
	}

	this->BackGround.setTexture(&this->BackGroundTexture);
}

void MainMenuState::InitFont()
{
	if (!this->font.loadFromFile("..\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void MainMenuState::InitButtons()
{
	using namespace gui;
	this->MainMenuState_Btn["Button_NewGame"] = new Button(gui::p2pX(8,vm), gui::p2pY(13, vm),
		gui::p2pX(12, vm), gui::p2pY(7, vm),
		&this->font, "New Game", gui::CharacterSize(vm), Color(100, 100, 200, 50),
		Color(50, 150, 200, 125),
		Color(30, 30, 70, 180), Color(100, 100, 200, 150),
		Color(50, 150, 200, 185),
		Color(30, 30, 70, 230));

	this->MainMenuState_Btn["Button_Settings"] = new Button(gui::p2pX(8, vm), gui::p2pY(27, vm),
		gui::p2pX(12, vm), gui::p2pY(7, vm),
		&this->font, "Settings", gui::CharacterSize(vm), Color(100, 100, 200, 50),
		Color(50, 150, 200, 125),							
		Color(30, 30, 70, 180), Color(100, 100, 200, 150),	
		Color(50, 150, 200, 185),							
		Color(30, 30, 70, 230));							
															
	this->MainMenuState_Btn["Button_Edit"] = new Button(gui::p2pX(8, vm), gui::p2pY(47, vm),
		gui::p2pX(12, vm), gui::p2pY(7, vm),
		&this->font, "Edit", gui::CharacterSize(vm), Color(100, 100, 200, 50),
		Color(50, 150, 200, 125),							
		Color(30, 30, 70, 180), Color(100, 100, 200, 150),	
		Color(50, 150, 200, 185),							
		Color(30, 30, 70, 230));							
	this->MainMenuState_Btn["Button_Exit"] = new Button(gui::p2pX(8, vm), gui::p2pY(68, vm),
		gui::p2pX(12, vm), gui::p2pY(7, vm),
		&this->font, "Exit", gui::CharacterSize(vm), Color(255, 0, 0, 50),
		Color(255, 100, 100, 125),
		Color(150, 0, 0, 180), Color(255, 0, 0, 150),
		Color(255, 100, 100, 185),
		Color(150, 0, 0, 230));
}

void MainMenuState::InitKeyBinds()
{
	ifstream ifs("..\\Config\\MainMenuKey_binds.ini");

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

MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
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

void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButton()
{

	for (auto& it : this->MainMenuState_Btn)
	{
		it.second->update(this->MousePosWindow);
	}

	if (this->MainMenuState_Btn["Button_NewGame"]->isPressed())
	{
		this->states->push(new GameState(this->Statedata));
	}
	if (this->MainMenuState_Btn["Button_Settings"]->isPressed())
	{
		this->states->push(new SettingsState(this->Statedata));
	}
	if (this->MainMenuState_Btn["Button_Edit"]->isPressed())
	{
		this->states->push(new EditorState(this->Statedata));
	}

	if (this->MainMenuState_Btn["Button_Exit"]->isPressed())
	{
		this->EndState();
	}
}

void MainMenuState::renderButton(RenderTarget& target)
{

	for (auto& it : this->MainMenuState_Btn)
	{
		it.second->render(target);
	}
}

void MainMenuState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->updateInput(dt);
	this->BackGround.setSize(
		Vector2f(
			static_cast<float>(this->Statedata->GFXSettings->resolution.width),
			static_cast<float>(this->Statedata->GFXSettings->resolution.height)
		)
	);

	this->updateButton();

}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(this->BackGround);
	this->renderButton(*target);

	Text mousetext;
	mousetext.setPosition(MousePosView + Vector2f(15, 10));
	mousetext.setFont(font);
	mousetext.setCharacterSize(15);
	stringstream ss;
	ss << MousePosView.x << " " << MousePosView.y;
	mousetext.setString(ss.str());
	target->draw(mousetext);
}
