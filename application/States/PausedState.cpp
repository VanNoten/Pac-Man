#include "PausedState.h"

#include "MenuState.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

namespace application {

PausedState::PausedState(StateManager& stateManager) : _stateManager(stateManager) {}

void PausedState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        _stateManager.popState(); // Continue playing
    }

    // Check if mouse button was pressed inside any of the buttons
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};

        if (_resumeButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.popState(); // Continue playing
        }

        if (_mainMenuButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<MenuState>(_stateManager)); // Return to main menu
        }
    }
}

void PausedState::update() {}

void PausedState::render(sf::RenderWindow& window) {
    sf::Font font = ResourceLoader::getInstance().getFont();

    sf::RectangleShape backgroundRect({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
    backgroundRect.setFillColor(sf::Color({0, 0, 0, 230}));
    backgroundRect.setPosition({0, 0});
    window.draw(backgroundRect);

    float centerX = window.getSize().x / 2.0f;
    float centerY = window.getSize().y / 2.0f;

    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString("Resume Game");
    tempText.setCharacterSize(36);
    float buttonWidth = tempText.getLocalBounds().width * 1.6f;
    float buttonHeight = tempText.getLocalBounds().height * 2.0f;
    float buttonSpacing = 40.0f;

    float totalHeight = (buttonHeight * 2) + buttonSpacing;
    float yPosition = centerY - totalHeight / 2.0f;

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString("Resume Game");
    resumeText.setCharacterSize(36);
    resumeText.setFillColor(sf::Color::White);

    sf::RectangleShape resumeRect({buttonWidth, buttonHeight});
    resumeRect.setPosition(centerX - buttonWidth / 2.0f, yPosition);
    resumeRect.setFillColor(sf::Color::Blue);

    _resumeButtonBounds = resumeRect.getGlobalBounds();

    // Center the text inside the button rectangle
    sf::FloatRect textBounds = resumeText.getLocalBounds();
    resumeText.setPosition(
        resumeRect.getPosition().x + resumeRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        resumeRect.getPosition().y + resumeRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(resumeRect);
    window.draw(resumeText);

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

    // Center the text inside the button rectangle
    sf::FloatRect mainMenuTextBounds = mainMenuText.getLocalBounds();
    mainMenuText.setPosition(mainMenuRect.getPosition().x + mainMenuRect.getSize().x / 2.0f -
                                 (mainMenuTextBounds.left + mainMenuTextBounds.width / 2.0f),
                             mainMenuRect.getPosition().y + mainMenuRect.getSize().y / 2.0f -
                                 (mainMenuTextBounds.top + mainMenuTextBounds.height / 2.0f));

    window.draw(mainMenuRect);
    window.draw(mainMenuText);
}

} // namespace application