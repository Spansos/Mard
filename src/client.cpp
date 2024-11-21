#include "client.hpp"

#include "common.hpp"

Client::Client(sf::IpAddress server_address, int server_port) {
    auto status = server.connect( server_address, server_port );
    if (status != sf::Socket::Done)
        ERROR_PRINT("couldn't connect to " + server_address.toString() + ":" + std::to_string(server_port));
    INFO_PRINT("connected to server: " + server.getRemoteAddress().toString() + ":" + std::to_string(server.getRemotePort()));
    window.create({1024, 720}, "Stellarium");
    window.setFramerateLimit(60);
}

void Client::run() {
    while (true) {
        server.setBlocking(false);
        sf::Packet packet;
        auto status = server.receive(packet);
        if (status == sf::Socket::Disconnected) {
            ERROR_PRINT("server closed");
            goto exit_game_loop;
        } else if (status == sf::Socket::Error) {
            ERROR_PRINT("error on receiving packets");
            goto exit_game_loop;
        } else if (status == sf::Socket::Done) {
            state.perform_action(*static_cast<const Action*>(packet.getData()));
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                goto exit_game_loop;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                perform_action_pwetty_pwease_👉👈(
                    Action{
                        .type=Action::ActionType::MAKE,
                        .make={
                            {
                                static_cast<float>(event.mouseButton.x),
                                static_cast<float>(event.mouseButton.y)
                            }
                        }
                    }
                );
            }
        }
        render();
    }
exit_game_loop:
    window.close();
}

void Client::perform_action_pwetty_pwease_👉👈(Action action) {
    sf::Packet packet;
    packet.append(&action, sizeof(Action));

    server.setBlocking(true);
    auto status = server.send(packet);

    if (status != sf::Socket::Done)
        ERROR_PRINT("no fucking ding dong");
}

void Client::render() {
    static sf::CircleShape shape;
    window.clear(sf::Color{16, 16, 24});
    for (sf::Vector2f entity : state.entities) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(entity);
        shape.setRadius(16);
        window.draw(shape);
    }
    window.display();
}