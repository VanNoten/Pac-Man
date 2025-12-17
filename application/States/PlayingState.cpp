#include "PlayingState.h"

#include "PausedState.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <Util/Stopwatch.h>

namespace application {

PlayingState::PlayingState(StateManager& stateManager)
    : _stateManager(stateManager), _world(std::make_unique<logic::World>()){};

void PlayingState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _stateManager.pushState(std::make_unique<PausedState>(_stateManager));
        }

        if (event.key.code == sf::Keyboard::Up) {
            _world->getPacman().setDirection(logic::Direction::UP);
        } else if (event.key.code == sf::Keyboard::Down) {
            _world->getPacman().setDirection(logic::Direction::DOWN);
        } else if (event.key.code == sf::Keyboard::Left) {
            _world->getPacman().setDirection(logic::Direction::LEFT);
        } else if (event.key.code == sf::Keyboard::Right) {
            _world->getPacman().setDirection(logic::Direction::RIGHT);
        }
    }
}

void PlayingState::update() {
    if (!_mapLoaded) {
        const std::vector<std::string> map = {"####################", "#....#........#....#", "#.##.#.######.#.##.#",
                                              "#.#..............#.#", "#.#.##.##..##.##.#.#", "#......#....#......#",
                                              "#.#.##.######.##.#.#", "#.#..............#.#", "#.##.#.######.#.##.#",
                                              "#....#....@...#....#", "####################"};
        _world->loadMap(map);
        _mapLoaded = true;
    }

    float deltaTime = static_cast<float>(logic::Stopwatch::getInstance()->getDeltaTime());
    _world->update(deltaTime);
}

void PlayingState::render(sf::RenderWindow& window) {
    if (!_camera) {
        _camera = std::make_unique<logic::Camera>(window.getSize().x, window.getSize().y);
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

    const auto& pacman = _world->getPacman();
    float screenX;
    float screenY;
    _camera->worldToScreen(pacman.getX(), pacman.getY(), screenX, screenY);
    float radius = _camera->worldToScreenSize(pacman.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);
    circle.setFillColor(sf::Color::Yellow);
    window.draw(circle);
}

} // namespace application