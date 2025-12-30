#include "GameOverState.h"

#include "MenuState.h"
#include "PlayingState.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

namespace application {

GameOverState::GameOverState(StateManager& stateManager) : _stateManager(stateManager) {}

void GameOverState::handleEvent(const sf::Event& event) {
    // Check if mouse button was pressed inside any of the buttons
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

        if (_restartButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<PlayingState>(_stateManager)); // Restart game
        }

        if (_mainMenuButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<MenuState>(_stateManager)); // Return to main menu
        }
    }
}

void GameOverState::update() {}

void GameOverState::render(sf::RenderWindow& window) {
    sf::Font font = ResourceLoader::getInstance().getFont();

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(72);
    gameOverText.setFillColor(sf::Color::Yellow);
    gameOverText.setPosition(centerX - gameOverText.getLocalBounds().width / 2.0f, 100.0f);
    window.draw(gameOverText);

    // Calculate how big one button is so we can vertically center two buttons
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString("Restart Game");
    tempText.setCharacterSize(36);
    float buttonWidth = tempText.getLocalBounds().width * 1.6f;
    float buttonHeight = tempText.getLocalBounds().height * 2.0f;
    float buttonSpacing = 40.0f;

    float totalHeight = (buttonHeight * 2) + buttonSpacing;
    float yPosition = centerY - totalHeight / 2.0f;

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setString("Restart Game");
    restartText.setCharacterSize(36);
    restartText.setFillColor(sf::Color::White);

    sf::RectangleShape restartRect({buttonWidth, buttonHeight});
    restartRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    restartRect.setFillColor(sf::Color::Blue);

    _restartButtonBounds = restartRect.getGlobalBounds();

    // Check if mouse button was pressed inside any of the buttons
    sf::FloatRect textBounds = restartText.getLocalBounds();
    restartText.setPosition(
        restartRect.getPosition().x + restartRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        restartRect.getPosition().y + restartRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(restartRect);
    window.draw(restartText);

    yPosition += buttonHeight + buttonSpacing;

    sf::Text mainMenuText;
    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(36);
    mainMenuText.setFillColor(sf::Color::White);

    sf::RectangleShape mainMenuRect({buttonWidth, buttonHeight});
    mainMenuRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    mainMenuRect.setFillColor(sf::Color::Blue);

    _mainMenuButtonBounds = mainMenuRect.getGlobalBounds();

    // Check if mouse button was pressed inside any of the buttons
    sf::FloatRect mainMenuTextBounds = mainMenuText.getLocalBounds();
    mainMenuText.setPosition(mainMenuRect.getPosition().x + mainMenuRect.getSize().x / 2.0f -
                                 (mainMenuTextBounds.left + mainMenuTextBounds.width / 2.0f),
                             mainMenuRect.getPosition().y + mainMenuRect.getSize().y / 2.0f -
                                 (mainMenuTextBounds.top + mainMenuTextBounds.height / 2.0f));

    window.draw(mainMenuRect);
    window.draw(mainMenuText);
}

} // namespace application