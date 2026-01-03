#include "VictoryState.h"

#include "MenuState.h"
#include "PlayingState.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <utility>

namespace application::states {

VictoryState::VictoryState(StateManager& stateManager, std::shared_ptr<logic::Score> score, const int livesLeft,
                           const int currentLevel)
    : _stateManager(stateManager), _score(std::move(score)), _livesLeft(livesLeft), _currentLevel(currentLevel) {}

void VictoryState::handleEvent(const sf::Event& event) {
    // Check if mouse button was pressed inside any of the buttons
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

        if (_nextLevelButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<PlayingState>(
                _stateManager, _score, _livesLeft,
                _currentLevel + 1)); // Transition to new PlayingState with incremented level
        }

        if (_mainMenuButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<MenuState>(_stateManager)); // Return to main menu
        }
    }
}

void VictoryState::update() {}

void VictoryState::render(sf::RenderWindow& window) {
    sf::Font font = ResourceLoader::getInstance().getFont();

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    float centerX = windowWidth / 2.0f;
    float centerY = windowHeight / 2.0f;

    sf::Text levelClearText;
    levelClearText.setFont(font);
    levelClearText.setString("Level Cleared");
    levelClearText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.15f));
    levelClearText.setFillColor(sf::Color::Yellow);
    levelClearText.setPosition(centerX - levelClearText.getLocalBounds().width / 2.0f, 100.0f);
    window.draw(levelClearText);

    // Calculate how big one button is so we can vertically center two buttons
    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString("Next Level");
    tempText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.07f));
    float buttonWidth = tempText.getLocalBounds().width * 1.6f;
    float buttonHeight = tempText.getLocalBounds().height * 2.0f;
    float buttonSpacing = windowHeight * 0.05f;

    float totalHeight = (buttonHeight * 2) + buttonSpacing;
    float yPosition = centerY - totalHeight / 2.0f;

    sf::Text nextLevelText;
    nextLevelText.setFont(font);
    nextLevelText.setString("Next Level");
    nextLevelText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.07f));
    nextLevelText.setFillColor(sf::Color::White);

    sf::RectangleShape nextLevelRect({buttonWidth, buttonHeight});
    nextLevelRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    nextLevelRect.setFillColor(sf::Color::Blue);

    _nextLevelButtonBounds = nextLevelRect.getGlobalBounds();

    // Check if mouse button was pressed inside any of the buttons
    sf::FloatRect textBounds = nextLevelText.getLocalBounds();
    nextLevelText.setPosition(
        nextLevelRect.getPosition().x + nextLevelRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        nextLevelRect.getPosition().y + nextLevelRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(nextLevelRect);
    window.draw(nextLevelText);

    yPosition += buttonHeight + buttonSpacing;

    sf::Text mainMenuText;
    mainMenuText.setFont(font);
    mainMenuText.setString("Main Menu");
    mainMenuText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.07f));
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

} // namespace application::states