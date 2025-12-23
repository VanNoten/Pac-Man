#include "Pacman.h"

namespace logic {

Pacman::Pacman(const float x, const float y, const float width, const float height)
    : EntityModel(x, y, width, height) {}

void Pacman::update(const float deltaTime) {
    const float moveDistance = _speed * deltaTime;

    switch (_direction) {
    case Direction::UP:
        _y += moveDistance;
        break;
    case Direction::DOWN:
        _y -= moveDistance;
        break;
    case Direction::RIGHT:
        _x += moveDistance;
        break;
    case Direction::LEFT:
        _x -= moveDistance;
        break;
    }
}

Bounds Pacman::getNextBounds(float deltaTime) const {
    const float moveDistance = _speed * deltaTime;
    float nextX = _x;
    float nextY = _y;

    switch (_direction) {
    case Direction::UP:
        nextY += moveDistance;
        break;
    case Direction::DOWN:
        nextY -= moveDistance;
        break;
    case Direction::RIGHT:
        nextX += moveDistance;
        break;
    case Direction::LEFT:
        nextX -= moveDistance;
        break;
    }

    float halfWidth = _width / 2.0f;
    float halfHeight = _height / 2.0f;

    return {nextX - halfWidth, nextX + halfWidth, nextY - halfHeight, nextY + halfHeight};
}

void Pacman::setDirection(const Direction direction) { _direction = direction; }

Direction Pacman::getDirection() const { return _direction; }

void Pacman::setWantedDirection(Direction direction) { _wantedDirection = direction; }

Direction Pacman::getWantedDirection() const { return _wantedDirection; }

} // namespace logic