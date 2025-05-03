#include "..//stdafx.h"
#include "GameState.h"

// ------------- Ініціалізація ресурсів -----------------

void GameState::InitTexture()
{
    Weapon.loadFromFile("..\\All_Texture\\Weapon\\no outline original.png");
}

void GameState::InitShaders()
{
    if (!this->core_shader.loadFromFile("..\\Shaders\\Vertex_Shader.glslv", "..\\Shaders\\Fragment_Shader.glslf"))
    {
        std::cerr << "ERROR::GAMESTATE::COULD NOT LOAD SHADERS" << "\n";
    }
}

void GameState::InitPlayers()
{
    if (this->mode == ONLINE_GAME_STATE::SERVER)
    {
        this->player = std::make_unique<Player>(gui::p2pX(50, vm), gui::p2pY(50, vm), this->temp, Weapon);
    }
    else
    {
        this->player = std::make_unique<Player>(gui::p2pX(50, vm), gui::p2pY(50, vm), this->temp, Weapon);
    }
}

void GameState::InitPlayerGUI()
{
    this->playerGUI = std::make_unique<PlayerGUI>(player.get());
}

void GameState::InitEnemySystem()
{
    this->Enemy_System = std::make_unique<EnemySystem>(enemies, this->temp);
}

// ------------- Конструктор GameState -----------------

GameState::GameState(StateData* state_data, const int state)
    : State(state_data), mode(state) // mode = ONLINE_GAME_STATE::CLIENT або SERVER
{
    if (mode == ONLINE_GAME_STATE::CLIENT)
    {
        this->InitClient();
    }
    if (mode == ONLINE_GAME_STATE::SERVER)
    {
        this->InitServer();
    }
    this->InitView();
    this->InitTileMap();
    this->InitEnemySystem();
    this->InitDeferredRender();
    this->InitFont();
    this->InitKeyBinds();
    this->InitTexture();
    this->InitShaders();
    this->InitPmenu();
    this->InitAnimations();
    this->InitPlayers();
    this->InitEnemy();
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
    this->pmenu = std::make_unique<PauseMenu>(vm, this->font);
    this->pmenu->AddButtons("RESUME", gui::p2pY(33, vm), gui::CharacterSize(vm), "Resume");
    this->pmenu->AddButtons("SAVE", gui::p2pY(46, vm), gui::CharacterSize(vm), "SAVE");
    this->pmenu->AddButtons("LOAD", gui::p2pY(60, vm), gui::CharacterSize(vm), "Load");
    this->pmenu->AddButtons("QUIT", gui::p2pY(74, vm), gui::CharacterSize(vm), "Quit");
}

GameState::~GameState()
{
    if (mode == ONLINE_GAME_STATE::CLIENT && clientSocket)
    {
        clientSocket->disconnect();
    }
    
    // Smart pointers will handle cleanup automatically
}

// ------------- Мережеві функції (TCP) -----------------

// Оновлення мережевої логіки
void GameState::UpdateMp(const float& dT)
{
    if (mode == ONLINE_GAME_STATE::SERVER)
    {
        try {
            netS.update();
            auto clientPositions = netS.getPlayerPositions();
            clientPositions["Host"] = {this->player->getPosition().x, this->player->getPosition().y};
            
            sf::Packet allPositionsPacket;
            allPositionsPacket << "ALL_POSITIONS" << clientPositions.size();
            for (const auto& pair : clientPositions)
            {
                allPositionsPacket << pair.first << pair.second.first << pair.second.second;
            }
            netS.broadcastToAll(allPositionsPacket);
        }
        catch (const std::exception& e) {
            std::cerr << "Server error: " << e.what() << std::endl;
        }
    }
    else if (mode == ONLINE_GAME_STATE::CLIENT)
    {
        static float pingTimer = 0.0f;
        pingTimer += dT;

        try {
            if (!clientSocket)
            {
                static float reconnectTimer = 0;
                reconnectTimer += dT;
                if (reconnectTimer >= 5.0f)
                {
                    reconnectTimer = 0;
                    InitClient();
                }
                return;
            }

            // Send ping every 2 seconds to keep connection alive
            if (pingTimer >= 2.0f)
            {
                pingTimer = 0.0f;
                sf::Packet pingPacket;
                pingPacket << "PING";
                if (clientSocket->send(pingPacket) != sf::Socket::Done)
                {
                    std::cout << "Client: Failed to send ping packet.\n";
                }
            }

            sf::Packet packet;
            while (clientSocket && clientSocket->receive(packet) == sf::Socket::Done)
            {
                std::string header;
                if (packet >> header)
                {
                    if (header == "NEW")
                    {
                        std::string newClientName;
                        float posX, posY;
                        if (packet >> newClientName >> posX >> posY)
                        {
                            if (newClientName != clientName)
                            {
                                createPlayers(posX, posY, newClientName);
                            }
                        }
                    }
                    else if (header == "ALL_POSITIONS")
                    {
                        int numPlayers;
                        if (packet >> numPlayers)
                        {
                            for (int i = 0; i < numPlayers; ++i)
                            {
                                std::string name;
                                float posX, posY;
                                if (packet >> name >> posX >> posY)
                                {
                                    auto it = std::find_if(multiplayerPlayers.begin(), multiplayerPlayers.end(),
                                        [&name](const MultiPlayer& mp) { return mp.name == name; });

                                    if (it != multiplayerPlayers.end())
                                    {
                                        if (it->players)
                                        {
                                            it->players->SetPosition(posX, posY);
                                        }
                                    }
                                    else if (name != clientName)
                                    {
                                        createPlayers(posX, posY, name);
                                    }
                                }
                            }
                        }
                    }
                    else if (header == "PONG")
                    {
                        // Reset ping timer on pong received
                        pingTimer = 0.0f;
                    }
                }
            }

            // Send position update
            if (clientSocket)
            {
                sf::Packet movePacket;
                movePacket << "MOVE" << clientName << this->player->getPosition().x << this->player->getPosition().y;
                if (clientSocket->send(movePacket) != sf::Socket::Done)
                {
                    std::cout << "Client: Connection lost, will attempt to reconnect.\n";
                    clientSocket->disconnect();
                    clientSocket = nullptr;
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Client error: " << e.what() << std::endl;
            if (clientSocket) {
                clientSocket->disconnect();
                clientSocket = nullptr;
            }
        }
    }
}

// ------------- Інші методи GameState -----------------

void GameState::updatePlayer(const float& dt)
{
    // Оновлення головного гравця
}

void GameState::updateEnemy(const float& dt)
{
    for (const auto& enemy : this->enemies)
    {
        if (enemy)
        {
            enemy->update(dt);
        }
    }
}

void GameState::InitKeyBinds()
{
    ifstream ifs("..\\Config\\Key_binds.ini");
    if (ifs.is_open())
    {
        string key, Key2;
        while (ifs >> key >> Key2)
        {
            this->KeyBinds[key] = this->supportedKey->at(Key2);
        }
    }
    ifs.close();
}

void GameState::InitAnimations()
{
    // Завантаження анімацій для ворогів
    {
        temp["Enemy_Idle_Top"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Run_Top"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Attack_Top"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Idle_Left"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Run_Left"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Attack_Left"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Idle_Right"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Run_Right"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Attack_Right"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Idle_Bottom"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Run_Bottom"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
        temp["Enemy_Attack_Bottom"].loadFromFile("..\\All_Texture\\Enemy\\Spider Sprite Sheet.png");
    }
    // Завантаження анімацій для гравця
    {
        temp["Idle_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_idle.png");
        temp["Run_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_walk.png");
        temp["Attack_Top"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Back animations\\spr_player_back_attack.png");
        temp["Idle_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_idle.png");
        temp["Run_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_walk.png");
        temp["Attack_Left"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_left_attack.png");
        temp["Idle_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_idle.png");
        temp["Run_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_walk.png");
        temp["Attack_Right"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Side animations\\spr_player_right_attack.png");
        temp["Idle_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_idle.png");
        temp["Run_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_walk.png");
        temp["Attack_Bottom"].loadFromFile("..\\All_Texture\\ALTERNATIVE\\Pixelarium - Playable Character - Free Version\\Pack Content\\Front animations\\spr_player_front_attack.png");
    }
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
    this->Tilemap->updateWorldBoundsCollision(this->player.get(), dt);
    this->Tilemap->updateTilesCollision(this->player.get(), dt);
    this->Tilemap->update_tiles(this->player.get(), dt, *this->Enemy_System);

    for (const auto& enemy : this->enemies)
    {
        if (enemy)
        {
            this->Tilemap->updateWorldBoundsCollision(enemy.get(), dt);
            this->Tilemap->updateTilesCollision(enemy.get(), dt);
        }
    }
}

void GameState::UpdateView(const float& dt)
{
    this->view.setCenter(floor(this->player->getPosition().x + 
                          (static_cast<float>(this->MousePosWindow.x) - static_cast<float>(this->Statedata->GFXSettings->resolution.width / 2)) / 10.f),
                          floor(this->player->getPosition().y + 
                          (static_cast<float>(this->MousePosWindow.y) - static_cast<float>(this->Statedata->GFXSettings->resolution.height / 2)) / 10.f));
    if (this->Tilemap->GetMaxSizeF().x >= this->view.getSize().x)
    {
        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
        {
            this->view.setCenter(this->view.getSize().x / 2.f, this->view.getCenter().y);
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
            this->view.setCenter(this->view.getCenter().x, this->view.getSize().y / 2.f);
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
    if (!this->paused)
    {
        this->UpdateView(dt);
        this->UpdatePlayerInput(dt);
        this->UpdateTileMap(dt);

        // Оновлення локального гравця
        this->player->update(dt, this->MousePosView);
        this->playerGUI->update(dt);

        // ОНОВЛЮЄМО МЕРЕЖУ
        this->UpdateMp(dt);
        for(const auto& mp : multiplayerPlayers)
        {
            if(mp.players)
            {
                std::cout << mp.players->GetPosition().x << " " << mp.players->GetPosition().y << std::endl;
            }
        }

        // Оновлюємо ворогів
        for (const auto& enemy : enemies)
        {
            if(enemy)
            {
                enemy->update(dt);
            }
        }
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

void GameState::createPlayers(float x, float y, const string& name)
{
    auto newPlayer = new Player(x, y, this->temp, Weapon);
    multiplayerPlayers.emplace_back(MultiPlayer(name, newPlayer));
}

// Клієнтська ініціалізація (TCP)
void GameState::InitClient()
{
    if (clientSocket)
    {
        clientSocket->disconnect();
        clientSocket = nullptr;
    }

    clientSocket = std::make_unique<sf::TcpSocket>();
    sf::IpAddress serverIP = "127.0.0.1";
    unsigned short serverPort = 58294;

    // Try to connect with timeout
    sf::Time timeout = sf::seconds(5);
    if (clientSocket->connect(serverIP, serverPort, timeout) == sf::Socket::Done)
    {
        std::cout << "Client: Connected to server at "
                  << serverIP << ":" << serverPort << "\n";

        // Set socket to blocking mode for registration
        clientSocket->setBlocking(true);

        // Generate a unique client name
        std::string myName = "Client_" + std::to_string(std::time(nullptr));
        
        // Send registration packet
        sf::Packet regPacket;
        regPacket << "REG" << myName;
        
        if (clientSocket->send(regPacket) == sf::Socket::Done)
        {
            std::cout << "Client: Registration packet sent.\n";
            
            // Wait for registration acknowledgment
            sf::Packet ackPacket;
            sf::Clock regTimer;
            bool registered = false;

            while (regTimer.getElapsedTime() < timeout)
            {
                sf::Socket::Status status = clientSocket->receive(ackPacket);
                if (status == sf::Socket::Done)
                {
                    std::string header;
                    if (ackPacket >> header && header == "REG_ACK")
                    {
                        std::cout << "Client: Registration acknowledged by server.\n";
                        this->clientName = myName;
                        registered = true;
                        break;
                    }
                }
                else if (status == sf::Socket::Disconnected)
                {
                    std::cout << "Client: Disconnected while waiting for registration acknowledgment.\n";
                    break;
                }
                sf::sleep(sf::milliseconds(50));
            }

            if (!registered)
            {
                std::cout << "Client: Registration timeout.\n";
                clientSocket->disconnect();
                clientSocket = nullptr;
            }
        }
        else
        {
            std::cout << "Client: Failed to send registration packet.\n";
            clientSocket->disconnect();
            clientSocket = nullptr;
        }

        // Set back to non-blocking mode if still connected
        if (clientSocket)
        {
            clientSocket->setBlocking(false);
        }
    }
    else
    {
        std::cout << "Client: Failed to connect to server.\n";
        clientSocket = nullptr;
    }
}

void GameState::InitServer()
{
    if (netS.init(58294) == sf::Socket::Done)
        std::cout << "Server: Initialized successfully.\n";
    else
        std::cout << "Server: Initialization failed.\n";
}

void GameState::InitView()
{
    // Налаштування view (якщо потрібно)\n
}

void GameState::InitEnemy()
{
    // Ініціалізація ворогів (якщо потрібно)\n
}

void GameState::render(RenderTarget* target)
{
    if (!target) target = this->window;

    this->renderTexture.clear();
    this->renderTexture.setView(this->view);

    this->Tilemap->render(renderTexture,
        this->viewPos,
        &this->core_shader,
        this->player->getCenter(),
        false);

    // Рендер мультиплеєрних гравців
    for (const auto& mp : multiplayerPlayers)
    {
        if (mp.players)
        {
            mp.players->render(this->renderTexture, &core_shader, false);
        }
    }

    // Рендер локального гравця
    this->player->render(this->renderTexture, &core_shader, false, this->player->getCenter());

    // Рендер ворогів
    for (const auto& enemy : enemies)
    {
        if (enemy)
        {
            enemy->render(this->renderTexture, &core_shader, false, this->player->getCenter());
        }
    }

    this->Tilemap->renderDeferrent(this->renderTexture,
        &this->core_shader,
        this->player->getCenter());

    this->playerGUI->Render_Dynamical(renderTexture);
    this->renderTexture.setView(this->renderTexture.getDefaultView());
    this->playerGUI->Render(this->renderTexture);

    if (this->paused)
        this->pmenu->render(this->renderTexture);

    this->renderTexture.display();
    target->draw(this->renderSprite);
}

void GameState::InitTileMap()
{
    this->Tilemap = std::make_unique<TileMap>("Puk.txt");
}
