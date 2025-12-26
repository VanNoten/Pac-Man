#include "Ghost.h"

namespace logic {

Ghost::Ghost(const float x, const float y, const float width, const float height, const GhostType ghostType)
    : EntityModel(x, y, width, height), _ghostType(ghostType) {}

void Ghost::update(float deltaTime) {}

void Ghost::move(const float x, const float y) {
    _x += x;
    _y += y;
}

void Ghost::setPosition(const float x, const float y) {
    _x = x;
    _y = y;
}

float Ghost::getSpeed() const { return _speed; }

GhostType Ghost::getGhostType() const { return _ghostType; }

void Ghost::setDirection(const Direction direction) { _direction = direction; }

Direction Ghost::getDirection() const { return _direction; }

void Ghost::setLastDecisionTile(const int tileX, const int tileY) {
    _lastDecisionTileX = tileX;
    _lastDecisionTileY = tileY;
}

int Ghost::getLastDecisionTileX() const { return _lastDecisionTileX; }

int Ghost::getLastDecisionTileY() const { return _lastDecisionTileY; }

} // namespace logic