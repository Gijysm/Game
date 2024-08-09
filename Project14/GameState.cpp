#include "stdafx.h"
#include "GameState.h"


void GameState::InitTexture()
{
	Weapon.loadFromFile("..\\All_Texture\\Weapon\\no outline original.png");
	temp["Idle_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_idle.png");
	this->texture["Idle_Top"] = temp["Idle_Top"];																													     							 
	temp["Run_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_walk.png");
	this->texture["Run_Top"] = temp["Run_Top"];																															 							 
	temp["Attack_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_attack.png");
	this->texture["Attack_Top"] = temp["Attack_Top"];
	temp["Idle_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_idle.png");
	this->texture["Idle_Left"] = temp["Idle_Left"];																																		   
	temp["Run_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_walk.png");
	this->texture["Run_Left"] = temp["Run_Left"];																														  				   
	temp["Attack_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_attack.png");
	this->texture["Attack_Left"] = temp["Attack_Left"];																																		
	temp["Idle_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_idle.png");
	this->texture["Idle_Right"] = temp["Idle_Right"];																													  				
	temp["Run_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_walk.png");
	this->texture["Run_Right"] = temp["Run_Right"];																														  
	temp["Attack_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_attack.png");
	this->texture["Attack_Right"] = temp["Attack_Right"];
	temp["Idle_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_idle.png");
	this->texture["Idle_Bottom"] = temp["Idle_Bottom"];
	temp["Run_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_walk.png");
	this->texture["Run_Bottom"] = temp["Run_Bottom"];
	temp["Attack_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_attack.png");
	this->texture["Attack_Bottom"] = temp["Attack_Bottom"];
}

void GameState::InitShaders()
{
	if (!this->core_shader.loadFromFile("..\\Shaders\\Vertex_Shader.glslv"
		, "..\\Shaders\\Fragment_Shader.glslf"))
	{
		cerr << "ERROR::GAMESTATE::COULD NOT LOAD SHADERS" << "\n";
	}
}

void GameState::InitPlayers()
{
	this->player = new Player(gui::p2pX(50, vm), gui::p2pY(50, vm), this->temp, Weapon);
}

void GameState::InitPlayerGUI()
{
	this->playerGUI = new PlayerGUI(player);
}

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->InitView();
	this->InitTileMap();
	this->InitDeferredRender();
	this->InitFont();
	this->InitKeyBinds();
	this->InitTexture();
	this->InitShaders();
	this->InitPmenu();
	this->InitPlayers();
	this->InitPlayerGUI();
}
void GameState::InitFont()
{
	if (!this->font.loadFromFile("..\\Font\\DungeonFont.ttf"))
	{
		throw "Error";
	}
}
void GameState::InitPmenu()
{
	this->pmenu = new PauseMenu(vm, this->font);
	this->pmenu->AddButtons("RESUME", gui::p2pY(33, vm),gui::CharacterSize(vm), "Resume");
	this->pmenu->AddButtons("SAVE", gui::p2pY(46, vm)  ,gui::CharacterSize(vm), "SAVE");
	this->pmenu->AddButtons("LOAD", gui::p2pY(60, vm)  ,gui::CharacterSize(vm), "Load");
	this->pmenu->AddButtons("QUIT", gui::p2pY(74, vm)  ,gui::CharacterSize(vm), "Quit");
}
GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->playerGUI;
	delete this->Tilemap;
}


void GameState::InitKeyBinds()
{
	ifstream ifs("..\\Config\\Key_binds.ini");

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

void GameState::UpdatePlayerInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_LEFT"))))
	{
		player->move(-1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_RIGHT"))))
	{
		player->move(1.f, 0.f, dt);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_UP"))))
	{
		player->move(0.f, -1.f, dt);
		this->player->getAtributeComponent()->gainHP(1);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->KeyBinds.at("MOVE_DOWN"))))
	{
		player->move(0.f, 1.f, dt);
		this->player->getAtributeComponent()->loseHP(1);
	}

}

void GameState::InitDeferredRender()
{
	this->renderTexture.create(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0, 
		this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
}

void GameState::UpdateTileMap(const float& dt)
{
	//this->Tilemap->update();
	this->Tilemap->updateCollision(player, dt);
}

void GameState::UpdateView(const float& dt)
{
	//unsigned i = -100;
	this->view.setCenter(floor(this->player->getPosition().x + (static_cast<float>(this->MousePosWindow.x) - static_cast<float>(this->Statedata->GFXSettings->resolution.width / 2)) / 10.f),
		floor(this->player->getPosition().y + (static_cast<float>(this->MousePosWindow.y) - static_cast<float>(this->Statedata->GFXSettings->resolution.height / 2)) / 10.f)
		);
	if (this->Tilemap->GetMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0 + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->Tilemap->GetMaxSizeF().x)
		{
			this->view.setCenter(this->Tilemap->GetMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	if (this->Tilemap->GetMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0 + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->Tilemap->GetMaxSizeF().y)
		{
			this->view.setCenter(this->view.getCenter().x, this->Tilemap->GetMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}
	
}

void GameState::updateInput(const float& dt)
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

void GameState::update(const float& dt)
{
	this->UpdateMousePosition(&this->view);
	this->UpdateKeyTime(dt);
	this->updateInput(dt);
	if(!this->paused)
	{
		this->UpdateView(dt);
		this->UpdatePlayerInput(dt);
		this->UpdateTileMap(dt);
		this->player->update(dt, this->MousePosView);
		this->playerGUI->update(dt);
		this->playerGUI->UpdateDynamicalElliments();
	}
	else
	{
		this->pmenu->update(this->MousePosWindow);
		this->updateButtons();
	}
	this->viewPos.x = static_cast<int>(this->view.getCenter().x / this->Statedata->GridSize);
	this->viewPos.y = static_cast<int>(this->view.getCenter().y / this->Statedata->GridSize);
}

void GameState::updateButtons()
{
	if (this->pmenu->isButtonPressed("RESUME"))
	{
		this->UnPausedState();
	}
	if (this->pmenu->isButtonPressed("QUIT") && this->GetKeyTime())
	{
		this->EndState();
	}
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::InitView()
{
	this->view.setSize(Vector2f(this->Statedata->GFXSettings->resolution.width,
		this->Statedata->GFXSettings->resolution.height));
	this->view.setCenter(this->Statedata->GFXSettings->resolution.width / 2.f,
		this->Statedata->GFXSettings->resolution.height / 2.f);
}

void GameState::render(RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderTexture.clear();
	this->renderTexture.setView(this->view);

	this->Tilemap->render(renderTexture, 
		this->viewPos,
		&this->core_shader, 
		this->player->getCenter(), 
		false);
	//Text mousetext;
	//mousetext.setFont(this->font);
	//mousetext.setCharacterSize(15);
	//mousetext.setPosition(MousePosView + Vector2f(5, 10));

	//stringstream ss;
	//ss << MousePosView.x << " " << MousePosView.y;
	//mousetext.setString(ss.str());

	//this->renderTexture.draw(mousetext);
	this->player->render(this->renderTexture, &core_shader);
	this->Tilemap->renderDeferrent(this->renderTexture, &this->core_shader, this->player->getCenter());
	this->playerGUI->Render_Dynamical(renderTexture);
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->Render(this->renderTexture);
	// Render pause menu if paused
	if (this->paused)
	{
		this->pmenu->render(this->renderTexture);
	}
	this->renderTexture.display();
	target->draw(this->renderSprite);
}


void GameState::InitTileMap()
{
	this->Tilemap = new TileMap("Puk.txt");
}
