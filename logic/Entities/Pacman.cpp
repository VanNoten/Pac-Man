#include "Pacman.h"

namespace logic {

Pacman::Pacman(const float x, const float y, const float width, const float height)
    : EntityModel(x, y, width, height) {}

void Pacman::update(const float deltaTime) {}

void Pacman::move(const float x, const float y) {
    _x += x;
    _y += y;
}

void Pacman::setPosition(const float x, const float y) {
    _x = x;
    _y = y;
}

float Pacman::getSpeed() const { return _speed; }

void Pacman::setDirection(const Direction direction) { _direction = direction; }

Direction Pacman::getDirection() const { return _direction; }

void Pacman::setWantedDirection(Direction direction) { _wantedDirection = direction; }

Direction Pacman::getWantedDirection() const { return _wantedDirection; }

} // namespace logic