#include "VictoryState.h"

#include "MenuState.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace application {

VictoryState::VictoryState(StateManager& stateManager) : _stateManager(stateManager) {}

void VictoryState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

        if (_nextLevelButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.popState();
        }

        if (_mainMenuButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<MenuState>(_stateManager));
        }
    }
}

void VictoryState::update() {}

void VictoryState::render(sf::RenderWindow& window) {
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    sf::RectangleShape backgroundRect({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    backgroundRect.setFillColor(sf::Color({0, 0, 0, 230}));
    backgroundRect.setPosition({0, 0});
    window.draw(backgroundRect);

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    sf::Text levelClearText;
    levelClearText.setFont(arial);
    levelClearText.setString("Level Cleared");
    levelClearText.setCharacterSize(72);
    levelClearText.setFillColor(sf::Color::Yellow);
    levelClearText.setPosition(centerX - levelClearText.getLocalBounds().width / 2.0f, 100.0f);
    window.draw(levelClearText);

    sf::Text tempText;
    tempText.setFont(arial);
    tempText.setString("Next Level");
    tempText.setCharacterSize(36);
    float buttonWidth = tempText.getLocalBounds().width * 1.6f;
    float buttonHeight = tempText.getLocalBounds().height * 2.0f;
    float buttonSpacing = 40.0f;

    float totalHeight = (buttonHeight * 2) + buttonSpacing;
    float yPosition = centerY - totalHeight / 2.0f;

    sf::Text nextLevelText;
    nextLevelText.setFont(arial);
    nextLevelText.setString("Next Level");
    nextLevelText.setCharacterSize(36);
    nextLevelText.setFillColor(sf::Color::White);

    sf::RectangleShape nextLevelRect({buttonWidth, buttonHeight});
    nextLevelRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    nextLevelRect.setFillColor(sf::Color::Blue);

    _nextLevelButtonBounds = nextLevelRect.getGlobalBounds();

    sf::FloatRect textBounds = nextLevelText.getLocalBounds();
    nextLevelText.setPosition(
        nextLevelRect.getPosition().x + nextLevelRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        nextLevelRect.getPosition().y + nextLevelRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(nextLevelRect);
    window.draw(nextLevelText);

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