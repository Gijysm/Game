#include "EditorState.h"

EditorState::EditorState(RenderWindow* window, map<string, int>* supportedKey, stack<State*>* states)
	:State(window, supportedKey, states)
{
	this->InitVariables();
	this->InitBackGround();
	this->InitFont();
	this->InitKeyBinds();
	this->InitButtons();
}

EditorState::~EditorState()
{
}


void EditorState::InitVariables()
{
}

void EditorState::InitBackGround()
{

}

void EditorState::InitFont()
{
	if (!this->font.loadFromFile("C:\\Users\\popka\\source\\repos\\Project14\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void EditorState::InitButtons()
{

}



void EditorState::InitKeyBinds()
{
	ifstream ifs("C:\\Users\\popka\\source\\repos\\Project14\\Config\\EditorKey_binds.ini");

	if (ifs.is_open())
	{
		string key = "";
		string Key2 = "";

		while (ifs >> key >> Key2)
		{
			this->KeyBinds[key] = this->supportedKey->at(Key2);
		}
	}
	else
	{
		throw "Error";
	}
	ifs.close();
}


void EditorState::Update_Input(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))))
	{
		this->EndState();
	}
}

void EditorState::updateButton()
{
}

void EditorState::renderButton(RenderTarget* target)
{

	for (auto& it : this->MainMenuState_Btn)
	{
		it.second->render(target);;
	}
}

void EditorState::update(const float& dt)
{
	this->UpdateMousePosition();
	this->Update_Input(dt);
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
	this->updateButton();
}

void EditorState::render(RenderTarget* target)
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