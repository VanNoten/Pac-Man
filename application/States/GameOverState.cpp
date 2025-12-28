#include "GameOverState.h"

#include "MenuState.h"
#include "PlayingState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

namespace application {

GameOverState::GameOverState(StateManager& stateManager) : _stateManager(stateManager) {}

void GameOverState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

        if (_restartButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
        }

        if (_mainMenuButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<MenuState>(_stateManager));
        }
    }
}

void GameOverState::update() {}

void GameOverState::render(sf::RenderWindow& window) {
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    sf::RectangleShape backgroundRect({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    backgroundRect.setFillColor(sf::Color({0, 0, 0, 230}));
    backgroundRect.setPosition({0, 0});
    window.draw(backgroundRect);

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    sf::Text gameOverText;
    gameOverText.setFont(arial);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setPosition(centerX - gameOverText.getLocalBounds().width / 2.0f, 100.0f);
    window.draw(gameOverText);

    sf::Text tempText;
    tempText.setFont(arial);
    tempText.setString("Restart Game");
    tempText.setCharacterSize(36);
    float buttonWidth = tempText.getLocalBounds().width * 1.6f;
    float buttonHeight = tempText.getLocalBounds().height * 2.0f;
    float buttonSpacing = 40.0f;

    float totalHeight = (buttonHeight * 2) + buttonSpacing;
    float yPosition = centerY - totalHeight / 2.0f;

    sf::Text restartText;
    restartText.setFont(arial);
    restartText.setString("Restart Game");
    restartText.setCharacterSize(36);
    restartText.setFillColor(sf::Color::White);

    sf::RectangleShape restartRect({buttonWidth, buttonHeight});
    restartRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    restartRect.setFillColor(sf::Color::Blue);

    _restartButtonBounds = restartRect.getGlobalBounds();

    sf::FloatRect textBounds = restartText.getLocalBounds();
    restartText.setPosition(
        restartRect.getPosition().x + restartRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        restartRect.getPosition().y + restartRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(restartRect);
    window.draw(restartText);

    yPosition += buttonHeight + buttonSpacing;

    sf::Text mainMenuText;
    mainMenuText.setFont(arial);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(36);
    mainMenuText.setFillColor(sf::Color::White);

    sf::RectangleShape mainMenuRect({buttonWidth, buttonHeight});
    mainMenuRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    mainMenuRect.setFillColor(sf::Color::Blue);

    _mainMenuButtonBounds = mainMenuRect.getGlobalBounds();

    sf::FloatRect mainMenuTextBounds = mainMenuText.getLocalBounds();
    mainMenuText.setPosition(mainMenuRect.getPosition().x + mainMenuRect.getSize().x / 2.0f -
                                 (mainMenuTextBounds.left + mainMenuTextBounds.width / 2.0f),
                             mainMenuRect.getPosition().y + mainMenuRect.getSize().y / 2.0f -
                                 (mainMenuTextBounds.top + mainMenuTextBounds.height / 2.0f));

    window.draw(mainMenuRect);
    window.draw(mainMenuText);
}

} // namespace application