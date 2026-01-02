#include "GhostView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application {

using namespace logic::entities;
using namespace logic::util;

GhostView::GhostView(const Ghost& ghost)
    : _model(ghost), _x(ghost.getX()), _y(ghost.getY()), _width(ghost.getWidth()),
      _directionIndex(static_cast<int>(ghost.getDirection())), _isFeared(ghost.getIsFeared()) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
    initializeSpriteRects();
    updateSpriteRect();
}

void GhostView::initializeSpriteRects() {
    // Calculate X offset based on ghost type
    int ghostTypeXOffset = X_OFFSET;
    switch (_model.getGhostType()) {
    case GhostType::Chaser:
        break;
    case GhostType::AheadChaser1:
        ghostTypeXOffset += SPRITE_SIZE + PIXELS_BETWEEN;
        break;
    case GhostType::AheadChaser2:
        ghostTypeXOffset += 2 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case GhostType::Locked:
        ghostTypeXOffset += 3 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    }

    // Spritesheet layout: RIGHT, DOWN, LEFT, UP
    // UP=0, DOWN=1, LEFT=2, RIGHT=3
    constexpr int directionOffsets[] = {6, 2, 4, 0}; // number of sprites that come before the direction

    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        for (int j = 0; j < NUM_FRAMES; j++) {
            const int y = Y_OFFSET + (j + directionOffsets[i]) * (SPRITE_SIZE + PIXELS_BETWEEN);
            _normalSpriteRects[i][j] = {ghostTypeXOffset, y, SPRITE_SIZE, SPRITE_SIZE};
        }
    }

    for (int i = 0; i < NUM_FRAMES; i++) {
        const int y = Y_OFFSET_FEARED + i * (SPRITE_SIZE + PIXELS_BETWEEN);
        _fearedSpriteRects[i] = {X_OFFSET_FEARED, y, SPRITE_SIZE, SPRITE_SIZE};
    }
}

void GhostView::updateSpriteRect() {
    if (_isFeared) {
        _sprite.setTextureRect(_fearedSpriteRects[_currentFrame]);
    } else {
        _sprite.setTextureRect(_normalSpriteRects[_directionIndex][_currentFrame]);
    }
}

void GhostView::onNotify(const logic::EventType event) {
    switch (event) {
    case logic::EventType::Move:
        _x = _model.getX();
        _y = _model.getY();
        break;
    case logic::EventType::DirectionChanged:
        _directionIndex = static_cast<int>(_model.getDirection());
        updateSpriteRect();
        break;
    case logic::EventType::FearedModeChanged:
        _isFeared = _model.getIsFeared();
        updateSpriteRect();
        break;
    default:
        break;
    }
}

void GhostView::draw(sf::RenderWindow& window, const Camera& camera, const float deltaTime) {
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

int GhostView::getZLevel() const { return _zLevel; }

} // namespace application