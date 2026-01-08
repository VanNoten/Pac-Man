#include "MenuState.h"
#include "PlayingState.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace application::states {

MenuState::MenuState(StateManager& stateManager)
    : _stateManager(stateManager), _score(std::make_shared<logic::Score>()), _highScores(_score->getHighscores()) {}

void MenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
        return;
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        // Check if mouse button was pressed inside the play button
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};
        if (_playButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
            return;
        }
    }
}

void MenuState::update() {}

void MenuState::render(sf::RenderWindow& window) {
    sf::Font font = ResourceLoader::getInstance().getFont();

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    float centerX = windowWidth / 2.0f;
    float yPosition = windowHeight * 0.05f;

    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Pac-Man");
    titleText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.15f));
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(centerX - titleText.getLocalBounds().width / 2.0f, yPosition);
    window.draw(titleText);
    yPosition += windowHeight * 0.2f;

    sf::Text scoresTitle;
    scoresTitle.setFont(font);
    scoresTitle.setString("Previous High Scores");
    scoresTitle.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.07f));
    scoresTitle.setFillColor(sf::Color::White);
    scoresTitle.setPosition(centerX - scoresTitle.getLocalBounds().width / 2.0f, yPosition);
    window.draw(scoresTitle);
    yPosition += windowHeight * 0.1f;

    if (_highScores.empty()) {
        sf::Text noScoresText;
        noScoresText.setFont(font);
        noScoresText.setString("No scores yet");
        noScoresText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.04f));
        noScoresText.setFillColor(sf::Color::White);
        noScoresText.setPosition(centerX - noScoresText.getLocalBounds().width / 2.0f, yPosition);
        window.draw(noScoresText);
    } else {
        for (int i = 0; i < _highScores.size(); i++) {
            sf::Text scoreText;
            scoreText.setFont(font);
            scoreText.setString(std::to_string(i + 1) + ". " + std::to_string(_highScores[i]));
            scoreText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.04f));
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(centerX - scoreText.getLocalBounds().width / 2.0f, yPosition);
            window.draw(scoreText);

            yPosition += windowHeight * 0.07f;
        }
    }

    yPosition += windowHeight * 0.1f;
    sf::Text playText;
    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(static_cast<unsigned int>(windowHeight * 0.07f));
    playText.setFillColor(sf::Color::White);

    sf::RectangleShape playRect({playText.getLocalBounds().width * 1.6f, playText.getLocalBounds().height * 2.0f});
    playRect.setPosition(centerX - playRect.getLocalBounds().width / 2.0f, yPosition);
    playRect.setFillColor(sf::Color::Blue);

    _playButtonBounds = playRect.getGlobalBounds();

    // Center the text inside the button rectangle
    sf::FloatRect textBounds = playText.getLocalBounds();
    playText.setPosition(
        playRect.getPosition().x + playRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        playRect.getPosition().y + playRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(playRect);
    window.draw(playText);
}

} // namespace application::states