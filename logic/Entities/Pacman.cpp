#include "Pacman.h"

namespace logic {

Pacman::Pacman(float x, float y, float width, float height, int spawnTileX, int spawnTileY)
    : EntityModel(x, y, width, height), _spawnTileX(spawnTileX), _spawnTileY(spawnTileY) {}

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

void Pacman::setWantedDirection(const Direction direction) { _wantedDirection = direction; }

Direction Pacman::getWantedDirection() const { return _wantedDirection; }

int Pacman::getSpawnTileX() const { return _spawnTileX; }

int Pacman::getSpawnTileY() const { return _spawnTileY; }

void Pacman::eatGhost() const { notify(EventType::GhostEaten); }

void Pacman::die() { _livesLeft -= 1; }

int Pacman::getLives() const { return _livesLeft; }

} // namespace logic