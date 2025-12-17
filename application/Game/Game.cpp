#include "Game.h"

#include "States/MenuState.h"
#include <SFML/Window/Event.hpp>
#include <Util/Stopwatch.h>

namespace application {

Game::Game() : _window(sf::VideoMode(1024, 768), "Pac-Man") {
    _stateManager.changeState(std::make_unique<MenuState>(_stateManager));
}
void Game::run() {
    while (_window.isOpen()) {
        double deltaTime = logic::Stopwatch::getInstance()->getDeltaTime();

        sf::Event event{};
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            else
                _stateManager.handleEvent(event);
        }

        _window.clear(sf::Color::Black);
        _stateManager.update();
        _stateManager.render(_window);
        _window.display();
    }
}

} // namespace application