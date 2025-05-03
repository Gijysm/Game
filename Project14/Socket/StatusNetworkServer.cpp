#include "..//stdafx.h"
#include "StatusNetworkServer.h"
#include <algorithm>

StatusNetworkServer::StatusNetworkServer() : running(false) {}

StatusNetworkServer::~StatusNetworkServer()
{
    stop();
}

void StatusNetworkServer::stop()
{
    running = false;
    if (networkThread.joinable())
    {
        networkThread.join();
    }
    
    // Очищаємо ресурси після зупинки потоку
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto &client : clientsVec)
    {
        if(client.socket)
        {
            client.socket->disconnect();
            delete client.socket;
            client.socket = nullptr;
        }
    }
    clientsVec.clear();
}

Socket::Status StatusNetworkServer::init(unsigned short port)
{
    if (running)
    {
        stop(); // Зупиняємо попередній потік, якщо він існує
    }

    if (listener.listen(port) == Socket::Done)
    {
        std::cout << "Server listening on port " << port << "\n";
        listener.setBlocking(false);
        running = true;
        try 
        {
            networkThread = std::thread(&StatusNetworkServer::networkLoop, this);
            return Socket::Done;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Failed to create network thread: " << e.what() << "\n";
            running = false;
            return Socket::Error;
        }
    }
    else
    {
        std::cerr << "Failed to listen on port " << port << "\n";
        return Socket::Error;
    }
}

void StatusNetworkServer::networkLoop()
{
    while (running)
    {
        try 
        {
            // Only try to accept new connections if we're not at capacity
            if (clientsVec.size() < 10) // Limit to 10 clients max
            {
                acceptConnection();
            }
            
            std::vector<Client*> disconnectedClients;
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                for (auto& client : clientsVec)
                {
                    if (!client.socket || !client.isConnected) 
                    {
                        disconnectedClients.push_back(&client);
                        continue;
                    }

                    sf::Packet inPacket;
                    sf::Socket::Status status = client.socket->receive(inPacket);
                    
                    if (status == sf::Socket::Done)
                    {
                        std::string header;
                        if (inPacket >> header)
                        {
                            if (header == "MOVE")
                            {
                                std::string clientName;
                                float x, y;
                                if (inPacket >> clientName >> x >> y)
                                {
                                    client.playerPosition = Vector2f(x, y);
                                }
                            }
                            else if (header == "PING")
                            {
                                // Send PONG back to keep connection alive
                                sf::Packet pongPacket;
                                pongPacket << "PONG";
                                client.socket->send(pongPacket);
                            }
                        }
                    }
                    else if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
                    {
                        disconnectedClients.push_back(&client);
                    }
                }
            }

            // Handle disconnected clients outside the lock
            for (auto* client : disconnectedClients)
            {
                handleClientDisconnection(*client);
            }
            
            cleanupDisconnectedClients();
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error in network loop: " << e.what() << "\n";
        }

        sf::sleep(milliseconds(16)); // ~60 updates per second
    }
}

void StatusNetworkServer::cleanupDisconnectedClients()
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    clientsVec.erase(
        std::remove_if(clientsVec.begin(), clientsVec.end(),
            [](const Client& client) { 
                return !client.isConnected || client.socket == nullptr; 
            }),
        clientsVec.end()
    );
}

void StatusNetworkServer::handleClientDisconnection(Client& client)
{
    if (!client.isConnected) return; // Уникаємо повторної обробки

    std::cout << "Client " << client.name << " disconnected\n";
    if (client.socket)
    {
        client.socket->disconnect();
        delete client.socket;
        client.socket = nullptr;
    }
    client.isConnected = false;
}

void StatusNetworkServer::acceptConnection()
{
    TcpSocket* newSocket = nullptr;
    try 
    {
        newSocket = new TcpSocket;
        
        // Set non-blocking mode for accept
        listener.setBlocking(false);
        Socket::Status acceptStatus = listener.accept(*newSocket);
        
        if (acceptStatus == Socket::Done)
        {
            std::cout << "New connection attempt from: " << newSocket->getRemoteAddress() << "\n";
            
            Client client;
            client.socket = newSocket;
            client.address = newSocket->getRemoteAddress();
            client.isConnected = true;
            client.playerPosition = Vector2f(0, 0);

            // Handle registration in blocking mode
            if (receiveRegistrationData(newSocket, client) == Socket::Done)
            {
                std::lock_guard<std::mutex> lock(clientsMutex);
                
                // Check if client with same name already exists
                auto existingClient = std::find_if(clientsVec.begin(), clientsVec.end(),
                    [&client](const Client& c) { return c.name == client.name; });
                
                if (existingClient != clientsVec.end())
                {
                    std::cout << "Client with name " << client.name << " already exists. Rejecting connection.\n";
                    newSocket->disconnect();
                    delete newSocket;
                    return;
                }
                
                sendConnectedClientsRecords(newSocket);
                clientsVec.push_back(std::move(client));
                broadcastNewClient(clientsVec.back());
            }
            else
            {
                std::cerr << "Failed to receive registration data from new client.\n";
                if (newSocket)
                {
                    newSocket->disconnect();
                    delete newSocket;
                }
            }
        }
        else if (acceptStatus != Socket::NotReady)
        {
            // Clean up on error, but not on NotReady (which just means no pending connection)
            delete newSocket;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error in acceptConnection: " << e.what() << "\n";
        if (newSocket)
        {
            newSocket->disconnect();
            delete newSocket;
        }
    }
}

std::map<std::string, std::pair<float, float>> StatusNetworkServer::getPlayerPositions()
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    std::map<std::string, std::pair<float, float>> positions;
    for (const auto& client : clientsVec)
    {
        if (client.isConnected && client.socket)
        {
            positions[client.name] = {client.playerPosition.x, client.playerPosition.y};
        }
    }
    return positions;
}

Socket::Status StatusNetworkServer::receiveRegistrationData(TcpSocket* socket, Client &client)
{
    if (!socket) return Socket::Error;

    // Set socket to blocking mode
    socket->setBlocking(true);
    
    sf::Packet packet;
    Socket::Status status = Socket::NotReady;
    sf::Clock regTimer;
    sf::Time timeout = sf::seconds(5);

    // Try to receive registration data with timeout
    while (regTimer.getElapsedTime() < timeout)
    {
        status = socket->receive(packet);
        if (status == Socket::Done)
        {
            std::string header;
            if (packet >> header && header == "REG")
            {
                std::string name;
                if (packet >> name)
                {
                    client.name = name;
                    std::cout << "Registered client with name: " << client.name << "\n";
                    
                    // Send acknowledgment
                    sf::Packet ackPacket;
                    ackPacket << "REG_ACK";
                    if (socket->send(ackPacket) == Socket::Done)
                    {
                        socket->setBlocking(false);
                        return Socket::Done;
                    }
                }
            }
            status = Socket::Error;
            break;
        }
        else if (status == sf::Socket::Disconnected)
        {
            std::cout << "Client disconnected during registration\n";
            break;
        }
        sf::sleep(sf::milliseconds(50));
    }
    
    // Reset socket to non-blocking mode
    socket->setBlocking(false);
    return status;
}

void StatusNetworkServer::broadcastToAll(const sf::Packet& packet)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto& client : clientsVec)
    {
        if (client.isConnected && client.socket)
        {
            sf::Packet packetCopy = packet;
            if (client.socket->send(packetCopy) != Socket::Done)
            {
                // Позначаємо клієнта як відключеного, якщо відправка не вдалася
                client.isConnected = false;
            }
        }
    }
}

void StatusNetworkServer::broadcastNewClient(const Client &newClient)
{
    if (!newClient.isConnected) return;

    sf::Packet packet;
    packet << "NEW" << newClient.name << newClient.playerPosition.x << newClient.playerPosition.y;
    
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto &c : clientsVec)
    {
        if (c.isConnected && c.socket && c.name != newClient.name)
        {
            if (c.socket->send(packet) != Socket::Done)
            {
                c.isConnected = false;
            }
        }
    }
}

Socket::Status StatusNetworkServer::sendConnectedClientsRecords(TcpSocket* socket)
{
    if (!socket) return Socket::Error;

    sf::Packet packet;
    std::lock_guard<std::mutex> lock(clientsMutex);
    
    packet << static_cast<int>(clientsVec.size());
    for (const auto &c : clientsVec)
    {
        if (c.isConnected)
        {
            packet << c.name << c.playerPosition.x << c.playerPosition.y;
        }
    }
    
    return socket->send(packet);
}

void StatusNetworkServer::update()
{
    // Мережевий цикл тепер обробляється в окремому потоці
}

vector<Client> StatusNetworkServer::getClients()
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    return clientsVec;
}

