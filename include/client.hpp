#pragma once

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "gamestate.hpp"

class Client {
public:
    Client(sf::IpAddress server_address, int server_port);
    void run();
private:
    void render();
    GameState state;
    sf::TcpSocket server;
    sf::RenderWindow window;
};