#include "PlayingState.h"

#include "GameOverState.h"
#include "MenuState.h"
#include "PausedState.h"
#include "VictoryState.h"

#include <Camera/Camera.h>
#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Util/Stopwatch.h>
#include <utility>

namespace application::states {

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
        // Pause game
        if (event.key.code == sf::Keyboard::Escape) {
            _stateManager.pushState(std::make_unique<PausedState>(_stateManager));
        }

        // Translate keyboard input to world actions
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
    // Load map if it hasn't been loaded yet
    if (!_mapLoaded) {
        const std::vector<std::string> map = {"####################", "#F...#........#....#", "#.##.#.######.#.##.#",
                                              "#.#..............#.#", "#.#.##.##  ##.##.#.#", "#......#1234#......#",
                                              "#.#.##.######.##.#.#", "#.#..............#.#", "#.##.#.######.#.##.#",
                                              "#....#....@...#...F#", "####################"};
        _world->loadMap(map, _livesLeft, _currentLevel);
        _world->addObserver(_score);

        _views = _sfmlFactory.getViews();
        // sort the views based off of z-level (so lower z-levels get rendered first) using lambda comparator
        std::sort(_views.begin(), _views.end(),
                  [](const std::shared_ptr<views::EntityView>& a, const std::shared_ptr<views::EntityView>& b) {
                      return a->getZLevel() < b->getZLevel();
                  });

        _mapLoaded = true;
    }

    _deltaTime = static_cast<float>(logic::util::Stopwatch::getInstance().getDeltaTime());

    _world->update(_deltaTime);
    _score->updateTick(_deltaTime);

    // Determine if state transition is needed
    if (_world->getIsGameOver()) {
        _stateManager.changeState(std::make_unique<GameOverState>(_stateManager));
        return;
    }

    if (_world->getIsGameVictory()) {
        int livesLeft = _world->getPacmanLives();
        _stateManager.changeState(std::make_unique<VictoryState>(_stateManager, _score, livesLeft, _currentLevel));
        return;
    }
}

void PlayingState::render(sf::RenderWindow& window) {
    if (!_camera) {
        _camera = std::make_unique<Camera>(window.getSize().x, window.getSize().y);
    } else {
        _camera->resize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    }

    // Render all entity views
    for (const auto& view : _views) {
        view->draw(window, *_camera, _deltaTime);
    }

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    sf::Font font = ResourceLoader::getInstance().getFont();

    float fontSize = windowHeight * 0.05f;
    float textYOffset = windowHeight - fontSize - windowHeight * 0.03f;

    float centerX = windowWidth / 2.0f;

    sf::Text levelText;
    levelText.setFont(font);
    levelText.setString("Level: " + std::to_string(_currentLevel));
    levelText.setCharacterSize(static_cast<unsigned int>(fontSize));
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setPosition(centerX - levelText.getLocalBounds().width / 2.0f, windowHeight * 0.03f);
    window.draw(levelText);

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(_score->getCurrentScore()));
    scoreText.setCharacterSize(static_cast<unsigned int>(fontSize));
    scoreText.setFillColor(sf::Color::Yellow);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setString("# Lives Remaining: " + std::to_string(_world->getPacmanLives()));
    livesText.setCharacterSize(static_cast<unsigned int>(fontSize));
    livesText.setFillColor(sf::Color::Yellow);

    float spacing = windowWidth * 0.05f;
    float combinedWidth = scoreText.getLocalBounds().width + spacing + livesText.getLocalBounds().width;
    float xOffset = centerX - combinedWidth / 2.0f;
    scoreText.setPosition(xOffset, textYOffset);
    livesText.setPosition(xOffset + scoreText.getLocalBounds().width + spacing, textYOffset);

    window.draw(scoreText);
    window.draw(livesText);
}

} // namespace application::states