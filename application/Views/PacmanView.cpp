#include "PacmanView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <Util/Stopwatch.h>

namespace application {

using namespace logic::entities;
using namespace logic::util;

PacmanView::PacmanView(const Pacman& pacman)
    : _model(pacman), _x(pacman.getX()), _y(pacman.getY()), _width(pacman.getWidth()),
      _directionIndex(static_cast<int>(pacman.getDirection())) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
    initializeSpriteRects();
    updateSpriteRect();
}

void PacmanView::initializeSpriteRects() {
    // Spritesheet layout: RIGHT, DOWN, LEFT, UP
    // UP=0, DOWN=1, LEFT=2, RIGHT=3
    constexpr int directionOffsets[] = {9, 3, 6, 0}; // number of sprites that come before the direction
    constexpr int xOffsets[] = {X_OFFSET, X_OFFSET - 1, X_OFFSET - 1, X_OFFSET}; // DOWN and LEFT are 1 pixel off

    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        for (int j = 0; j < NUM_FRAMES; j++) {
            const int x = xOffsets[i];
            const int y = Y_OFFSET + (j + directionOffsets[i]) * (SPRITE_SIZE + PIXELS_BETWEEN);
            _spriteRects[i][j] = {x, y, SPRITE_SIZE, SPRITE_SIZE};
        }
    }
}

void PacmanView::updateSpriteRect() { _sprite.setTextureRect(_spriteRects[_directionIndex][_currentFrame]); }

void PacmanView::onNotify(const logic::EventType event) {
    switch (event) {
    case logic::EventType::Move:
        _x = _model.getX();
        _y = _model.getY();
        break;
    case logic::EventType::DirectionChanged:
        _directionIndex = static_cast<int>(_model.getDirection());
        updateSpriteRect();
        break;
    default:
        break;
    }
}

void PacmanView::draw(sf::RenderWindow& window, const Camera& camera, const float deltaTime) {
    _animationTimer += deltaTime;

    if (_animationTimer >= ANIMATION_SPEED) {
        _animationTimer = 0.0f;
        _currentFrame = (_currentFrame + 1) % NUM_FRAMES;
        updateSpriteRect();
    }

    float screenX;
    float screenY;
    camera.worldToScreen(_x, _y, screenX, screenY);
    const float radius = camera.worldToScreenSize(_width * 0.5f);

    const float scale = (radius * 2.0f) / SPRITE_SIZE;
    _sprite.setScale(scale, scale);
    _sprite.setPosition(screenX - radius, screenY - radius);

    window.draw(_sprite);
}

int PacmanView::getZLevel() const { return _zLevel; }

} // namespace application