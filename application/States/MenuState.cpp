#include "MenuState.h"
#include "PlayingState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace application {

MenuState::MenuState(StateManager& stateManager) : _stateManager(stateManager) {}

void MenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
    }
}

void MenuState::update() {}

void MenuState::render(sf::RenderWindow& window) {
    sf::RectangleShape rect({200.f, 200.f});
    rect.setFillColor(sf::Color(255, 0, 0));
    window.draw(rect);
}

} // namespace application