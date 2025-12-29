#include "PlayingState.h"

#include "GameOverState.h"
#include "MenuState.h"
#include "PausedState.h"
#include "VictoryState.h"

#include <Camera/Camera.h>
#include <Resources/ResourceLoader.h>
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

        _views = _sfmlFactory.getViews();
        // sort the views based off of z-level (so lower z-levels get rendered first) using lambda comparator
        std::sort(_views.begin(), _views.end(),
                  [](const std::shared_ptr<EntityView>& a, const std::shared_ptr<EntityView>& b) {
                      return a->getZLevel() < b->getZLevel();
                  });

        _mapLoaded = true;
    }

    _deltaTime = static_cast<float>(logic::Stopwatch::getInstance()->getDeltaTime());

    _world->update(_deltaTime);
    _score->updateTick(_deltaTime);

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

    for (const auto& view : _views) {
        view->draw(window, *_camera, _deltaTime);
    }

    std::string posString =
        std::to_string(_world->getPacman().getX()) + ", " + std::to_string(_world->getPacman().getY());
    sf::Font font = ResourceLoader::getInstance()->getFont();
    sf::Text pos;
    pos.setFont(font);
    pos.setFillColor(sf::Color::Green);
    pos.setString(posString);
    window.draw(pos);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(_score->getCurrentScore()));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(0, 30);
    window.draw(scoreText);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setString("Lives: " + std::to_string(_world->getPacman().getLives()));
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(0, 60);
    window.draw(livesText);

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level: " + std::to_string(_world->getCurrentLevel()));
    levelText.setCharacterSize(24);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(0, 90);
    window.draw(levelText);
}

} // namespace application