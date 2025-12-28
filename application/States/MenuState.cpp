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
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = {event.mouseButton.x, event.mouseButton.y};
        if (_playButtonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            _stateManager.changeState(std::make_unique<PlayingState>(_stateManager));
        }
    }
}

void MenuState::update() {}

void MenuState::render(sf::RenderWindow& window) {
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    std::vector<int> scores = _score->getHighscores();

    float centerX = window.getSize().x / 2.0f;
    float yPosition = 20.0f;

    sf::Text titleText;
    titleText.setFont(arial);
    titleText.setString("Pac-Man");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(centerX - titleText.getLocalBounds().width / 2.0f, yPosition);
    window.draw(titleText);
    yPosition += 140.0f;

    sf::Text scoresTitle;
    scoresTitle.setFont(arial);
    scoresTitle.setString("Previous High Scores");
    scoresTitle.setCharacterSize(24);
    scoresTitle.setFillColor(sf::Color::White);
    scoresTitle.setPosition(centerX - scoresTitle.getLocalBounds().width / 2.0f, yPosition);
    window.draw(scoresTitle);
    yPosition += 40.0f;

    if (scores.empty()) {
        sf::Text noScoresText;
        noScoresText.setFont(arial);
        noScoresText.setString("No scores yet");
        noScoresText.setCharacterSize(18);
        noScoresText.setFillColor(sf::Color::White);
        noScoresText.setPosition(centerX - noScoresText.getLocalBounds().width / 2.0f, yPosition);
        window.draw(noScoresText);
    } else {
        for (int i = 0; i < scores.size(); i++) {
            sf::Text scoreText;
            scoreText.setFont(arial);
            scoreText.setString(std::to_string(i + 1) + ". " + std::to_string(scores[i]));
            scoreText.setCharacterSize(18);
            scoreText.setFillColor(sf::Color::White);
            scoreText.setPosition(centerX - scoreText.getLocalBounds().width / 2.0f, yPosition);
            window.draw(scoreText);

            yPosition += 35.0f;
        }
    }

    yPosition += 60.0f;
    sf::Text playText;
    playText.setFont(arial);
    playText.setString("Play");
    playText.setCharacterSize(36);
    playText.setFillColor(sf::Color::White);

    sf::RectangleShape playRect({playText.getLocalBounds().width * 1.6f, playText.getLocalBounds().height * 2.0f});
    playRect.setPosition(centerX - playRect.getLocalBounds().width / 2.0f, yPosition);
    playRect.setFillColor(sf::Color::Blue);

    _playButtonBounds = playRect.getGlobalBounds();

    sf::FloatRect textBounds = playText.getLocalBounds();
    playText.setPosition(
        playRect.getPosition().x + playRect.getSize().x / 2.0f - (textBounds.left + textBounds.width / 2.0f),
        playRect.getPosition().y + playRect.getSize().y / 2.0f - (textBounds.top + textBounds.height / 2.0f));

    window.draw(playRect);
    window.draw(playText);
}

} // namespace application