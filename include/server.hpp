#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <SFML/Network.hpp>

class Server {
public:
    Server(int port);
    // main loop.
    void run();
private:
    // looks for a new connection
    // if no one is trying to connect, it does nothing
    // if someone is trying to connect, it adds them to clients
    void try_new_connection();
    sf::TcpListener client_listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;
};