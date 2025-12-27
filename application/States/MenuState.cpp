#include "MenuState.h"
#include "PlayingState.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace application {

MenuState::MenuState(StateManager& stateManager)
    : _stateManager(stateManager), _score(std::make_shared<logic::Score>()) {}

void MenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
    }
}

void MenuState::update() {}

void MenuState::render(sf::RenderWindow& window) {
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    std::vector<int> scores = _score->getHighscores();

    for (int i = 0; i < scores.size(); i++) {
        sf::Text scoreText;
        scoreText.setFont(arial);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setString(std::to_string(scores[i]));
        scoreText.setPosition(window.getSize().x / 2, i * 30);
        window.draw(scoreText);
    }

    sf::RectangleShape rect({200.f, 200.f});
    rect.setFillColor(sf::Color(255, 0, 0));
    window.draw(rect);
}

} // namespace application