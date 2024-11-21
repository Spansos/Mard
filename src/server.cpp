#include "server.hpp"

#include "common.hpp"

Server::Server(int port) {
    client_listener.setBlocking(false);
    sf::Socket::Status status = client_listener.listen(port);
    if (status == sf::Socket::Status::Done)
        INFO_PRINT("server started on port " + std::to_string(client_listener.getLocalPort()));
    else
        ERROR_PRINT("error on server start:  " + std::to_string(status));
}

void Server::run() {
    while (true) {
        try_new_connection();
        for (size_t i=0; i<clients.size(); i++) {
            auto & client = *clients[i];
            sf::Packet packet;
            auto status = client.receive(packet);
            switch (status) {
                case sf::Socket::Disconnected:
                    INFO_PRINT("connection disconnected: " + client.getRemoteAddress().toString());
                    clients.erase(clients.begin()+i);
                    break;
                case sf::Socket::Error:
                    WARNING_PRINT("error receiving packets: " + status);
                    break;
                case sf::Socket::Done:
                    INFO_PRINT("received action");
                    break;
                default:
                    break;
            }
        }
        sf::sleep(sf::microseconds(1'000'000/tps));
    }
}

void Server::try_new_connection() {
    std::unique_ptr<sf::TcpSocket> new_client = std::make_unique<sf::TcpSocket>();
    sf::Socket::Status new_client_status = client_listener.accept(*new_client);
    if (new_client_status != sf::Socket::Status::Done)
        return;
    new_client->setBlocking(false);
    INFO_PRINT("new connection: " + new_client->getRemoteAddress().toString());
    clients.push_back(std::move(new_client));
}