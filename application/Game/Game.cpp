#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <Util/Stopwatch.h>

namespace application {

Game::Game() : _window(sf::VideoMode(1600, 1200), "Pac-Man") {}
void Game::run() {
    while (_window.isOpen()) {
        double deltaTime = logic::Stopwatch::getInstance()->getDeltaTime();

        sf::Event event{};
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        _window.clear(sf::Color::Black);

        _window.display();
    }
}

} // namespace application