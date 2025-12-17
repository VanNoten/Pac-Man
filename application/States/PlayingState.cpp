#include "PlayingState.h"

#include "PausedState.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
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

        switch (event.key.code) {
        case sf::Keyboard::Up:
            _world->handleAction(logic::Actions::UpArrow);
            break;
        case sf::Keyboard::Down:
            _world->handleAction(logic::Actions::DownArrow);
            break;
        case sf::Keyboard::Left:
            _world->handleAction(logic::Actions::LeftArrow);
            break;
        case sf::Keyboard::Right:
            _world->handleAction(logic::Actions::RightArrow);
            break;
        default:
            break;
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

    std::string posString =
        std::to_string(_world->getPacman().getX()) + ", " + std::to_string(_world->getPacman().getY());
    sf::Font arial;
    arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
    sf::Text pos;
    pos.setFont(arial);
    pos.setFillColor(sf::Color::Green);
    pos.setString(posString);
    window.draw(pos);
}

} // namespace application