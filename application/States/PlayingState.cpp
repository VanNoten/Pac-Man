#include "PlayingState.h"

#include "GameOverState.h"
#include "MenuState.h"
#include "PausedState.h"
#include "VictoryState.h"

#include <Camera/Camera.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Util/Stopwatch.h>
#include <utility>

namespace application {

PlayingState::PlayingState(StateManager& stateManager)
    : _stateManager(stateManager), _score(std::make_shared<logic::Score>()) {
    _sfmlFactory.setScoreObserver(_score);
    _world = std::make_unique<logic::World>(_sfmlFactory);
}

PlayingState::PlayingState(StateManager& stateManager, std::shared_ptr<logic::Score> score, const int livesLeft,
                           const int currentLevel)
    : _stateManager(stateManager), _score(std::move(score)), _livesLeft(livesLeft), _currentLevel(currentLevel) {
    _sfmlFactory.setScoreObserver(_score);
    _world = std::make_unique<logic::World>(_sfmlFactory);
}

void PlayingState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _stateManager.pushState(std::make_unique<PausedState>(_stateManager));
        }

        switch (event.key.code) {
        case sf::Keyboard::Up:
            _world->handleAction(logic::Actions::Up);
            break;
        case sf::Keyboard::Down:
            _world->handleAction(logic::Actions::Down);
            break;
        case sf::Keyboard::Left:
            _world->handleAction(logic::Actions::Left);
            break;
        case sf::Keyboard::Right:
            _world->handleAction(logic::Actions::Right);
            break;
        default:
            break;
        }
    }
}

void PlayingState::update() {
    if (!_mapLoaded) {
        const std::vector<std::string> map = {"####################", "#F...#........#....#", "#.##.#.######.#.##.#",
                                              "#.#..............#.#", "#.#.##.##..##.##.#.#", "#......#1234#......#",
                                              "#.#.##.######.##.#.#", "#.#..............#.#", "#.##.#.######.#.##.#",
                                              "#....#....@...#...F#", "####################"};
        _world->loadMap(map, _livesLeft, _currentLevel);
        _world->addObserver(_score);
        _mapLoaded = true;
    }

    float deltaTime = static_cast<float>(logic::Stopwatch::getInstance()->getDeltaTime());

    _world->update(deltaTime);
    _score->updateTick(deltaTime);

    if (_world->getIsGameOver()) {
        _stateManager.pushState(std::make_unique<GameOverState>(_stateManager));
    }

    if (_world->getIsGameVictory()) {
        int livesLeft = _world->getPacmanLives();
        _stateManager.pushState(std::make_unique<VictoryState>(_stateManager, _score, livesLeft, _currentLevel));
    }
}

void PlayingState::render(sf::RenderWindow& window) {
    if (!_camera) {
        _camera = std::make_unique<Camera>(window.getSize().x, window.getSize().y);
    }

    for (const auto& wall : _world->getWalls()) {
        float screenX;
        float screenY;
        _camera->worldToScreen(wall->getX(), wall->getY(), screenX, screenY);
        float width = _camera->worldToScreenSize(wall->getWidth());
        float height = _camera->worldToScreenSize(wall->getHeight());

        sf::RectangleShape rect({width, height});
        rect.setPosition(screenX - width * 0.5f, screenY - height * 0.5f);
        rect.setFillColor(sf::Color(0, 0, 255));
        window.draw(rect);
    }

    for (const auto& coin : _world->getCoins()) {
        if (coin->isCollected())
            continue;

        float screenX;
        float screenY;
        _camera->worldToScreen(coin->getX(), coin->getY(), screenX, screenY);
        float radius = _camera->worldToScreenSize(coin->getWidth() * 0.5f);

        sf::CircleShape circle(radius);
        circle.setPosition(screenX - radius, screenY - radius);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);
    }

    for (const auto& fruit : _world->getFruits()) {
        if (fruit->isCollected())
            continue;

        float screenX;
        float screenY;
        _camera->worldToScreen(fruit->getX(), fruit->getY(), screenX, screenY);
        float radius = _camera->worldToScreenSize(fruit->getWidth() * 0.5f);

        sf::CircleShape circle(radius);
        circle.setPosition(screenX - radius, screenY - radius);
        circle.setFillColor(sf::Color::Red);
        window.draw(circle);
    }

    for (const auto& ghost : _world->getActiveGhosts()) {
        float screenX;
        float screenY;
        _camera->worldToScreen(ghost->getX(), ghost->getY(), screenX, screenY);
        float radius = _camera->worldToScreenSize(ghost->getWidth() * 0.5f);

        sf::CircleShape circle(radius);
        circle.setPosition(screenX - radius, screenY - radius);

        if (!ghost->getIsFeared()) {
            switch (ghost->getGhostType()) {
            case logic::GhostType::Locked:
                circle.setFillColor(sf::Color::Red);
                break;
            case logic::GhostType::AheadChaser:
                circle.setFillColor(sf::Color::Magenta);
                break;
            case logic::GhostType::Chaser:
                circle.setFillColor(sf::Color::Yellow);
                break;
            default:
                break;
            }
        } else {
            circle.setFillColor(sf::Color::Green);
        }

        window.draw(circle);
    }

    const auto& pacman = _world->getPacman();
    float screenX;
    float screenY;
    _camera->worldToScreen(pacman.getX(), pacman.getY(), screenX, screenY);
    float radius = _camera->worldToScreenSize(pacman.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);
    circle.setFillColor(sf::Color::Yellow);
    window.draw(circle);

    std::string posString =
        std::to_string(_world->getPacman().getX()) + ", " + std::to_string(_world->getPacman().getY());
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    sf::Text pos;
    pos.setFont(arial);
    pos.setFillColor(sf::Color::Green);
    pos.setString(posString);
    window.draw(pos);

    sf::Text scoreText;
    scoreText.setFont(arial);
    scoreText.setString("Score: " + std::to_string(_score->getCurrentScore()));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(0, 30);
    window.draw(scoreText);

    sf::Text livesText;
    livesText.setFont(arial);
    livesText.setString("Lives: " + std::to_string(_world->getPacman().getLives()));
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(0, 60);
    window.draw(livesText);

    sf::Text levelText;
    levelText.setFont(arial);
    levelText.setString("Level: " + std::to_string(_world->getCurrentLevel()));
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(0, 90);
    window.draw(levelText);
}

} // namespace application