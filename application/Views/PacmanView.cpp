#include "PacmanView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <Util/Stopwatch.h>

namespace application {

PacmanView::PacmanView(const logic::Pacman& pacman) : _model(pacman) {
    const sf::Texture& texture = ResourceLoader::getInstance()->getSpriteSheet();
    _sprite.setTexture(texture);
}

void PacmanView::onNotify(const logic::EventType event) {}

void PacmanView::draw(sf::RenderWindow& window, const Camera& camera, const float deltaTime) {
    _animationTimer += deltaTime;

    if (_animationTimer >= ANIMATION_SPEED) {
        _animationTimer = 0.0f;
        _currentFrame = (_currentFrame + 1) % 3;
    }

    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    const float scale = (radius * 2.0f) / SPRITE_SIZE;
    _sprite.setScale(scale, scale);
    _sprite.setTextureRect(getSpriteRect());
    _sprite.setPosition(screenX - radius, screenY - radius);

    window.draw(_sprite);
}

sf::IntRect PacmanView::getSpriteRect() const {
    const Direction direction = _model.getDirection();
    int x = X_OFFSET;
    int y = Y_OFFSET;

    switch (direction) {
    case Direction::RIGHT:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::DOWN:
        x -= 1; // down direction is 1 pixel off on spritesheet
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 3 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::LEFT:
        x -= 1; // left direction is 1 pixel off on spritesheet
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 6 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::UP:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 9 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    }

    return {x, y, SPRITE_SIZE, SPRITE_SIZE};
}

} // namespace application