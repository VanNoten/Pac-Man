#include "PausedState.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

namespace application {

PausedState::PausedState(StateManager& stateManager) : _stateManager(stateManager) {}

void PausedState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        _stateManager.popState();
    }
}

void PausedState::update() {}

void PausedState::render(sf::RenderWindow& window) {
    sf::RectangleShape rect({400.f, 200.f});
    rect.setFillColor(sf::Color(0, 255, 0));
    window.draw(rect);
}

} // namespace application