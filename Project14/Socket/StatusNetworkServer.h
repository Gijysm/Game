#ifndef STATUS_NETWORK_SERVER_H
#define STATUS_NETWORK_SERVER_H

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;
using namespace sf;

struct Client {
    string name;
    TcpSocket* socket;      // Динамічно створений сокет
    IpAddress address;
    Vector2f playerPosition; // Можна оновлювати, якщо клієнт надсилає "MOVE" пакети
    bool isConnected;       // Флаг для відстеження стану підключення
};

class StatusNetworkServer
{
private:
    std::mutex clientsMutex;
    TcpListener listener;
    vector<Client> clientsVec;
    std::atomic<bool> running;
    std::thread networkThread;
    
    void networkLoop();
    void cleanupDisconnectedClients();
    
public:
    StatusNetworkServer();
    ~StatusNetworkServer();

    void broadcastToAll(const sf::Packet& packet);

    // Ініціалізація сервера (слухаємо на вказаному порту)
    Socket::Status init(unsigned short port);
    vector<Client> getClients();
    std::map<std::string, std::pair<float, float>> getPlayerPositions();
    // Головний цикл сервера
    void update();
    void stop();

private:
    // Приймаємо нове підключення, якщо є
    void acceptConnection();

    // Отримуємо реєстраційні дані від клієнта (очікуємо "REG" + name)
    Socket::Status receiveRegistrationData(TcpSocket* socket, Client &client);

    // Розсилаємо всім повідомлення про нового клієнта (пакет: "NEW" + name)
    void broadcastNewClient(const Client &newClient);
    
    // Відправляємо новому клієнту список вже підключених клієнтів
    Socket::Status sendConnectedClientsRecords(TcpSocket* socket);
    void handleClientDisconnection(Client& client);
};

#endif // STATUS_NETWORK_SERVER_H
