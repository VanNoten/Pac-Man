#include "Pacman.h"

namespace logic {

Pacman::Pacman(const float x, const float y) : EntityModel(x, y) {}

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

float Pacman::getWidth() const { return _size; }

float Pacman::getHeight() const { return _size; }

void Pacman::setDirection(const Direction direction) { _direction = direction; }

Direction Pacman::getDirection() const { return _direction; }

void Pacman::setSize(const float size) { _size = size; }

} // namespace logic