#include "World.h"

#include <cmath>

namespace logic {

World::World(AbstractFactory& factory) : _factory(factory) {}

void World::handleAction(Actions action) const {
    switch (action) {
    case Actions::Up:
        _pacman->setWantedDirection(Direction::UP);
        break;
    case Actions::Down:
        _pacman->setWantedDirection(Direction::DOWN);
        break;
    case Actions::Left:
        _pacman->setWantedDirection(Direction::LEFT);
        break;
    case Actions::Right:
        _pacman->setWantedDirection(Direction::RIGHT);
        break;
    default:
        break;
    }
}

void World::update(const float deltaTime) {
    handlePacmanMovement(deltaTime);

    for (const auto& coin : _coins) {
        if (!coin->isCollected() && isColliding(_pacman->getBounds(), coin->getBounds())) {
            coin->collect();
        }
    }
}

void World::loadMap(const std::vector<std::string>& map) {
    _walls.clear();
    if (map.empty())
        return;

    _map = map;

    const int rows = map.size();
    const int cols = map[0].size();

    _cell = 2.0f / std::max(cols, rows);

    const float totalWidth = _cell * cols;
    const float totalHeight = _cell * rows;

    _originX = -totalWidth * 0.5f;
    _originY = totalHeight * 0.5f;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const float x = _originX + _cell * (c + 0.5f);
            const float y = _originY - _cell * (r + 0.5f);

            switch (map[r][c]) {
            case '#':
                _walls.push_back(_factory.createWall(x, y, _cell, _cell));
                break;
            case '@':
                _pacman = _factory.createPacman(x, y, _cell * 0.9f, _cell * 0.9f);
                break;
            case '.':
                _coins.push_back(_factory.createCoin(x, y, _cell * 0.2f, _cell * 0.2f));
            default:
                break;
            }
        }
    }
}

const std::vector<std::unique_ptr<Wall>>& World::getWalls() const { return _walls; }

const std::vector<std::unique_ptr<Coin>>& World::getCoins() const { return _coins; }

Pacman& World::getPacman() const { return *_pacman; }

void World::handlePacmanMovement(const float deltaTime) const {
    if (!_pacman)
        return;

    const float speed = _pacman->getSpeed();
    const float moveDistance = speed * deltaTime;

    const float x = _pacman->getX();
    const float y = _pacman->getY();
    Direction currentDirection = _pacman->getDirection();
    const Direction wantedDirection = _pacman->getWantedDirection();

    bool isReverseDirection = false;
    if (currentDirection == Direction::LEFT && wantedDirection == Direction::RIGHT)
        isReverseDirection = true;
    if (currentDirection == Direction::RIGHT && wantedDirection == Direction::LEFT)
        isReverseDirection = true;
    if (currentDirection == Direction::UP && wantedDirection == Direction::DOWN)
        isReverseDirection = true;
    if (currentDirection == Direction::DOWN && wantedDirection == Direction::UP)
        isReverseDirection = true;

    if (isReverseDirection) {
        _pacman->setDirection(wantedDirection);
        currentDirection = wantedDirection;
    }

    const int tileX = getTileX(x);
    const int tileY = getTileY(y);
    const float centerX = getTileCenterX(tileX);
    const float centerY = getTileCenterY(tileY);

    float distanceToCenterTile = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
    if (distanceToCenterTile < moveDistance * moveDistance + 1e-4f) {
        if (wantedDirection != currentDirection) {
            int nextTileX = tileX;
            int nextTileY = tileY;

            switch (wantedDirection) {
            case Direction::UP:
                nextTileY--;
                break;
            case Direction::DOWN:
                nextTileY++;
                break;
            case Direction::LEFT:
                nextTileX--;
                break;
            case Direction::RIGHT:
                nextTileX++;
                break;
            }

            if (!isWallAtTile(nextTileX, nextTileY)) {
                _pacman->setPosition(centerX, centerY);
                _pacman->setDirection(wantedDirection);
                currentDirection = wantedDirection;
            }
        }

        int tileInfrontX = tileX;
        int tileInfrontY = tileY;
        switch (currentDirection) {
        case Direction::UP:
            tileInfrontY--;
            break;
        case Direction::DOWN:
            tileInfrontY++;
            break;
        case Direction::LEFT:
            tileInfrontX--;
            break;
        case Direction::RIGHT:
            tileInfrontX++;
            break;
        }

        if (isWallAtTile(tileInfrontX, tileInfrontY)) {
            _pacman->setPosition(centerX, centerY);
            return;
        }
    }

    float moveX = 0.0f;
    float moveY = 0.0f;
    switch (currentDirection) {
    case Direction::UP:
        moveY = moveDistance;
        break;
    case Direction::DOWN:
        moveY = -moveDistance;
        break;
    case Direction::LEFT:
        moveX = -moveDistance;
        break;
    case Direction::RIGHT:
        moveX = moveDistance;
        break;
    }

    _pacman->move(moveX, moveY);
}

bool World::isColliding(const Bounds& A, const Bounds& B) {
    return (A.left < B.right && A.right > B.left) && (A.top < B.bottom && A.bottom > B.top);
}

float World::getTileCenterX(const int tileX) const { return _originX + _cell * (tileX + 0.5f); }

float World::getTileCenterY(const int tileY) const { return _originY - _cell * (tileY + 0.5f); }

int World::getTileX(const float x) const { return static_cast<int>((x - _originX) / _cell); }

int World::getTileY(const float y) const { return static_cast<int>((_originY - y) / _cell); }

bool World::isWallAtTile(const int tileX, const int tileY) const {
    if (tileY < 0 || tileY >= _map.size())
        return true;
    if (tileX < 0 || tileX >= _map[0].size())
        return true;
    return _map[tileY][tileX] == '#';
}

} // namespace logic