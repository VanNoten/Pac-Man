#include "GhostView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application {

GhostView::GhostView(const logic::Ghost& ghost) : _model(ghost) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
}

void GhostView::onNotify(logic::EventType event) {}

void GhostView::draw(sf::RenderWindow& window, const Camera& camera, const float deltaTime) {
    _animationTimer += deltaTime;

    if (_animationTimer >= ANIMATION_SPEED) {
        _animationTimer = 0.0f;
        _currentFrame =
            (_currentFrame + 1) % 2; // Ghost sprites only have 2 frames so keep switching between frame 0 and 1
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

int GhostView::getZLevel() const { return _zLevel; }

sf::IntRect GhostView::getSpriteRect() const {
    if (_model.getIsFeared()) {
        const int y = Y_OFFSET_FEARED + _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN);
        return {X_OFFSET_FEARED, y, SPRITE_SIZE, SPRITE_SIZE};
    }

    const logic::GhostType ghostType = _model.getGhostType();
    const Direction direction = _model.getDirection();
    int x = X_OFFSET;
    int y = Y_OFFSET;

    switch (ghostType) {
    case logic::GhostType::Chaser:
        break;
    case logic::GhostType::AheadChaser1:
        x += SPRITE_SIZE + PIXELS_BETWEEN;
        break;
    case logic::GhostType::AheadChaser2:
        x += 2 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case logic::GhostType::Locked:
        x += 3 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    }

    switch (direction) {
    case Direction::RIGHT:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::DOWN:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 2 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::LEFT:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 4 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    case Direction::UP:
        y += _currentFrame * (SPRITE_SIZE + PIXELS_BETWEEN) + 6 * (SPRITE_SIZE + PIXELS_BETWEEN);
        break;
    }

    return {x, y, SPRITE_SIZE, SPRITE_SIZE};
}

} // namespace application