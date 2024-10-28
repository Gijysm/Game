#include "..//stdafx.h"
#include "EditorState.h"

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->InitVariables();
	this->InitEditorStates();
	// this->InitBackGround();
	this->InitView();
	this->InitFont();
	this->InitKeyBinds();
	this->InitButtons();
	this->InitPmenu();
	this->InitTileMap();
	this->InitGui();

	this->InitModes();
}

EditorState::~EditorState()
{
	delete this->pmenu; 
	delete this->Tilemap;
	for (int i = 0; i < this->EModes.size(); ++i)
	{
		delete this->EModes[i];
	}
}


void EditorState::InitEditorStates()
{
	this->editorStateData.vm = &this->vm;
	this->editorStateData.view = &this->MainView;
	this->editorStateData.font = &this->font;
	this->editorStateData.Keytime = &this->Keytime;
	this->editorStateData.KeytimeMax = &this->KeytimeMax;
	this->editorStateData.Key_binds= &this->KeyBinds;
	this->editorStateData.MousePosScreen = &this->MousePosScreen;
	this->editorStateData.MousePosWindow = &this->MousePosWindow;
	this->editorStateData.MousePosView = &this->MousePosView;
	this->editorStateData.MousePosGrid = &this->MousePosGrid;
}

void EditorState::InitVariables()
{
	int cam_speed = 100;
}

void EditorState::InitView()
{
	this->MainView.setSize(Vector2f(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
	this->MainView.setCenter(this->Statedata->GFXSettings->resolution.width / 2.f,
		this->Statedata->GFXSettings->resolution.height/ 2.f);
}
// void EditorState::InitBackGround()
// {
//
// }

void EditorState::InitFont()
{
	if (!this->font.loadFromFile("..\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}

void EditorState::InitButtons()
{
}



void EditorState::InitKeyBinds()
{
	ifstream ifs("..\\Config\\EditorKey_binds.ini");

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

void EditorState::InitPmenu()
{

	this->pmenu = new PauseMenu(vm, this->font);
	this->pmenu->AddButtons("RESUME", gui::p2pY(33, vm),gui::CharacterSize(vm), "Resume");
	this->pmenu->AddButtons("SAVE", gui::p2pY(46, vm)  ,gui::CharacterSize(vm), "SAVE");
	this->pmenu->AddButtons("LOAD", gui::p2pY(60, vm)  ,gui::CharacterSize(vm), "Load");
	this->pmenu->AddButtons("QUIT", gui::p2pY(74, vm)  ,gui::CharacterSize(vm), "Quit");
}

void EditorState::InitTileMap()
{
	this->Tilemap = new TileMap(this->Statedata->GridSize,16,16, 40, 40, "..\\All_Texture\\Grass\\GRASS.png");
}

void EditorState::InitGui()
{
}

void EditorState::InitModes()
{
	this->EModes.push_back(new DefaultEditorMode(this->Statedata, this->Tilemap, &this->editorStateData));
}


void EditorState::updateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("Close"))) && this->GetKeyTime())
	{
		if (!this->paused)
		{
			this->PausedState();
		}
		else
		{
			this->UnPausedState();
		}
	}
}
void EditorState::KeyTime(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->MainView.move(-cam_speed * dt, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->MainView.move(cam_speed * dt, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_UP"))))
	{
		this->MainView.move(0,-cam_speed * dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->MainView.move(0, cam_speed * dt);
	}

}

void EditorState::updatePmenuButton()
{
	if (this->pmenu->isButtonPressed("RESUME"))
	{
		this->UnPausedState();
	}
	if (this->pmenu->isButtonPressed("SAVE"))
	{
		this->Tilemap->saveToFile("Puk.txt");
	}
	if (this->pmenu->isButtonPressed("LOAD"))
	{
		this->Tilemap->loadFromFile("Puk.txt");
	}
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->EndState();
	}
}

void EditorState::updateButton()
{
}

void EditorState::updateGui(const float& dt)
{
}

void EditorState::UpdateEditorInput(const float& dt)
{
}

void EditorState::renderPmenuButton(RenderTarget& target)
{
	this->pmenu->render(target);
}

void EditorState::renderButton(RenderTarget& target)
{
}

void EditorState::renderGui(RenderTarget* target)
{
}

void EditorState::update(const float& dt)
{
	this->UpdateMousePosition(&this->MainView);
	this->UpdateKeyTime(dt);
	this->updateInput(dt);
	if (!this->paused)
	{
		this->KeyTime(dt);
		this->UpdateEditorInput(dt);
		this->updateGui(dt);
		this->EModes[static_cast<size_t>(EditorModes::DEFAULT_MODE)]->update(dt);
	}
	else
	{
		this->pmenu->update(this->MousePosWindow);
		this->updatePmenuButton();
	}
	//cout << this->MousePosView.x << "   " << this->MousePosView.y << "\n";
}
void EditorState::render(RenderTarget* target)
{	

	if (!target)
	{
		target = this->window;
	}
	target->setView(this->MainView);
	this->Tilemap->render(*target, this->MousePosGrid, NULL, Vector2f(), true);
	this->Tilemap->renderDeferrent(*target, NULL, Vector2f());
	this->EModes[static_cast<size_t>(EditorModes::DEFAULT_MODE)]->render(target);
	target->setView(this->window->getDefaultView());
	this->renderGui(target);
	if (paused)
	{
		target->setView(this->window->getDefaultView());
		this->renderPmenuButton(*target);
	}

}