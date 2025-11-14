#include "Game.h"
#include <SFML/Window/Event.hpp>

namespace application {

Game::Game() : window_(sf::VideoMode(1600, 1200), "Pac-Man") {}
void Game::run() {
    while (window_.isOpen()) {
        sf::Event event{};
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
        }

        window_.clear(sf::Color::Black);

        window_.display();
    }
}

} // namespace application