#include "Game.h"

#include "States/MenuState.h"
#include <SFML/Window/Event.hpp>
#include <Util/Stopwatch.h>

namespace application {

Game::Game() : _window(sf::VideoMode(1280, 720), "Pac-Man", sf::Style::Default) {
    _stateManager.changeState(std::make_unique<states::MenuState>(_stateManager));
}
void Game::run() {
    while (_window.isOpen()) {
        sf::Event event{};
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width),
                                          static_cast<float>(event.size.height));
                _window.setView(sf::View(visibleArea));
            }
            _stateManager.handleEvent(event);
        }

        _window.clear(sf::Color::Black);
        _stateManager.update();
        _stateManager.render(_window);
        _window.display();
    }
}

} // namespace application