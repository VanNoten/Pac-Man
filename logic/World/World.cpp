#include "World.h"

#include <Util/Random.h>
#include <algorithm>
#include <cmath>
#include <iostream>

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

    if (!_allGhostsActive) {
        activateGhosts(deltaTime);
    }

    if (_ghostsAreFeared) {
        _fearedTimer -= deltaTime;

        if (_fearedTimer <= 0.0f) {
            _fearedTimer = 0.0f;
            _ghostsAreFeared = false;

            for (const auto& ghost : _ghosts) {
                ghost->setIsFeared(false);
            }
        }
    }

    for (auto& ghost : _ghosts) {
        if (!ghost->getIsActive())
            continue;

        handleGhostMovement(*ghost, deltaTime);

        if (isColliding(_pacman->getBounds(), ghost->getBounds())) {
            if (ghost->getIsFeared()) {
                const int tileX = ghost->getSpawnTileX();
                const int tileY = ghost->getSpawnTileY();
                const float tileCenterX = getTileCenterX(tileX);
                const float tileCenterY = getTileCenterY(tileY);
                ghost->setPosition(tileCenterX, tileCenterY);
                ghost->setIsFeared(false);
                _pacman->eatGhost();
            }
        }
    }

    for (const auto& coin : _coins) {
        if (!coin->isCollected() && isColliding(_pacman->getBounds(), coin->getBounds())) {
            coin->collect();
        }
    }

    for (const auto& fruit : _fruits) {
        if (!fruit->isCollected() && isColliding(_pacman->getBounds(), fruit->getBounds())) {
            fruit->collect();
            fearGhosts();
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
                break;
            case 'F':
                _fruits.push_back(_factory.createFruit(x, y, _cell * 0.6f, _cell * 0.6f));
                break;
            case '1': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::Locked);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GHOST_1_DELAY);
            } break;
            case '2': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::AheadChaser);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GHOST_2_DELAY);
            } break;
            case '3': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::AheadChaser);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GHOST_3_DELAY);
            } break;
            case '4': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::Chaser);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GHOST_4_DELAY);
            } break;
            default:
                break;
            }
        }
    }
}

const std::vector<std::unique_ptr<Wall>>& World::getWalls() const { return _walls; }

const std::vector<std::unique_ptr<Coin>>& World::getCoins() const { return _coins; }

const std::vector<std::unique_ptr<Fruit>>& World::getFruits() const { return _fruits; }

const std::vector<std::unique_ptr<Ghost>>& World::getActiveGhosts() const { return _ghosts; }

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
            std::pair<int, int> nextTile = getTileInDirection(tileX, tileY, wantedDirection);

            if (!isWallAtTile(nextTile.first, nextTile.second)) {
                _pacman->setPosition(centerX, centerY);
                _pacman->setDirection(wantedDirection);
                currentDirection = wantedDirection;
            }
        }

        std::pair<int, int> tileInfront = getTileInDirection(tileX, tileY, currentDirection);

        if (isWallAtTile(tileInfront.first, tileInfront.second)) {
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

void World::handleGhostMovement(Ghost& ghost, const float deltaTime) const {
    const float speed = ghost.getSpeed();
    const float moveDistance = speed * deltaTime;

    const float x = ghost.getX();
    const float y = ghost.getY();
    const int tileX = getTileX(x);
    const int tileY = getTileY(y);
    const float centerX = getTileCenterX(tileX);
    const float centerY = getTileCenterY(tileY);

    Direction currentDirection = ghost.getDirection();

    bool isNewTile = tileX != ghost.getLastDecisionTileX() || tileY != ghost.getLastDecisionTileY();
    float distanceToCenterTile = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
    if (distanceToCenterTile < moveDistance * moveDistance + 1e-4f && isNewTile) {
        ghost.setLastDecisionTile(tileX, tileY);

        Direction nextDirection;
        if (!ghost.getIsFeared()) {
            nextDirection = getNextGhostDirection(ghost);
        } else {
            nextDirection = getNextFearedGhostDirection(ghost);
        }

        ghost.setDirection(nextDirection);
        if (currentDirection != nextDirection) {
            ghost.setPosition(centerX, centerY);
            currentDirection = nextDirection;
        }

        std::pair<int, int> tileInfront = getTileInDirection(tileX, tileY, currentDirection);

        if (isWallAtTile(tileInfront.first, tileInfront.second)) {
            ghost.setPosition(centerX, centerY);
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

    ghost.move(moveX, moveY);
}

void World::activateGhosts(const float deltaTime) {
    for (int i = 0; i < _ghostDelayTimers.size(); i++) {
        if (i < _ghosts.size() && !_ghosts[i]->getIsActive()) {
            if (_ghostDelayTimers[i] > 0.0f) {
                _ghostDelayTimers[i] -= deltaTime;
            }

            if (_ghostDelayTimers[i] <= 0.0f) {
                _ghosts[i]->setActive(true);
            }
        }
    }

    _allGhostsActive = true;
    for (const auto& ghost : _ghosts) {
        if (!ghost->getIsActive()) {
            _allGhostsActive = false;
            break;
        }
    }
}

void World::fearGhosts() {
    _fearedTimer = FEARED_MODE_DURATION;
    _ghostsAreFeared = true;

    for (const auto& ghost : _ghosts) {
        if (!ghost->getIsFeared()) {
            const Direction reverseDirection = getReverseDirection(ghost->getDirection());
            const int ghostTileX = getTileX(ghost->getX());
            const int ghostTileY = getTileY(ghost->getY());
            std::pair<int, int> reverseTile = getTileInDirection(ghostTileX, ghostTileY, reverseDirection);
            if (!isWallAtTile(reverseTile.first, reverseTile.second)) {
                ghost->setDirection(reverseDirection);
            }
        }

        ghost->setIsFeared(true);
    }
}

bool World::isColliding(const Bounds& A, const Bounds& B) {
    return (A.left < B.right && A.right > B.left) && (A.top < B.bottom && A.bottom > B.top);
}

float World::getTileCenterX(const int tileX) const { return _originX + _cell * (tileX + 0.5f); }

float World::getTileCenterY(const int tileY) const { return _originY - _cell * (tileY + 0.5f); }

int World::getTileX(const float x) const { return static_cast<int>((x - _originX) / _cell); }

int World::getTileY(const float y) const { return static_cast<int>((_originY - y) / _cell); }

std::pair<int, int> World::getTileInDirection(const int tileX, const int tileY, const Direction direction) {
    int tileInDirectionX = tileX;
    int tileInDirectionY = tileY;
    switch (direction) {
    case Direction::UP:
        tileInDirectionY--;
        break;
    case Direction::DOWN:
        tileInDirectionY++;
        break;
    case Direction::LEFT:
        tileInDirectionX--;
        break;
    case Direction::RIGHT:
        tileInDirectionX++;
        break;
    }

    return {tileInDirectionX, tileInDirectionY};
}

bool World::isWallAtTile(const int tileX, const int tileY) const {
    if (tileY < 0 || tileY >= _map.size())
        return true;
    if (tileX < 0 || tileX >= _map[0].size())
        return true;
    return _map[tileY][tileX] == '#';
}

int World::getManhattanDistance(const int fromTileX, const int fromTileY, const int toTileX, const int toTileY) {
    return abs(fromTileX - toTileX) + abs(fromTileY - toTileY);
}

Direction World::getReverseDirection(const Direction direction) {
    Direction reverseDirection = {};

    switch (direction) {
    case Direction::UP:
        reverseDirection = Direction::DOWN;
        break;
    case Direction::DOWN:
        reverseDirection = Direction::UP;
        break;
    case Direction::LEFT:
        reverseDirection = Direction::RIGHT;
        break;
    case Direction::RIGHT:
        reverseDirection = Direction::LEFT;
        break;
    default:
        break;
    }

    return reverseDirection;
}

std::vector<Direction> World::getPossibleDirections(const Ghost& ghost) const {
    std::vector<Direction> possibleDirections = {};
    const int tileX = getTileX(ghost.getX());
    const int tileY = getTileY(ghost.getY());

    Direction reverseDirection = getReverseDirection(ghost.getDirection());

    if (!isWallAtTile(tileX, tileY - 1) && reverseDirection != Direction::UP)
        possibleDirections.push_back(Direction::UP);

    if (!isWallAtTile(tileX, tileY + 1) && reverseDirection != Direction::DOWN)
        possibleDirections.push_back(Direction::DOWN);

    if (!isWallAtTile(tileX - 1, tileY) && reverseDirection != Direction::LEFT)
        possibleDirections.push_back(Direction::LEFT);

    if (!isWallAtTile(tileX + 1, tileY) && reverseDirection != Direction::RIGHT)
        possibleDirections.push_back(Direction::RIGHT);

    if (possibleDirections.empty())
        return {reverseDirection};

    return possibleDirections;
}

Direction World::getNextGhostDirection(const Ghost& ghost) const {
    GhostType ghostType = ghost.getGhostType();
    std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

    if (possibleDirections.size() == 1)
        return possibleDirections[0];

    if (ghostType == GhostType::Locked) {
        if (Random::getInstance()->chance(0.5)) {
            std::vector<Direction> filteredDirections;
            for (const auto direction : possibleDirections) {
                if (direction != ghost.getDirection()) {
                    filteredDirections.push_back(direction);
                }
            }

            if (!filteredDirections.empty()) {
                return filteredDirections[Random::getInstance()->randomIndex(filteredDirections.size())];
            }
        }

        bool canKeepGoing = false;
        for (const auto direction : possibleDirections) {
            if (direction == ghost.getDirection()) {
                canKeepGoing = true;
                break;
            }
        }

        if (canKeepGoing) {
            return ghost.getDirection();
        }
        return possibleDirections[Random::getInstance()->randomIndex(possibleDirections.size())];
    }

    if (ghostType == GhostType::AheadChaser) {
        std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

        if (possibleDirections.size() == 1)
            return possibleDirections[0];

        int minManhattanDistance = std::numeric_limits<int>::max();
        std::vector<Direction> bestDirections;

        const int pacTileX = getTileX(_pacman->getX());
        const int pacTileY = getTileY(_pacman->getY());
        std::pair<int, int> nextPacTile = getTileInDirection(pacTileX, pacTileY, _pacman->getDirection());

        const int ghostTileX = getTileX(ghost.getX());
        const int ghostTileY = getTileY(ghost.getY());

        for (const auto& direction : possibleDirections) {
            std::pair<int, int> nextGhostTile = getTileInDirection(ghostTileX, ghostTileY, direction);

            int manhattanDistance =
                getManhattanDistance(nextGhostTile.first, nextGhostTile.second, nextPacTile.first, nextPacTile.second);

            if (manhattanDistance < minManhattanDistance) {
                minManhattanDistance = manhattanDistance;
                bestDirections.clear();
                bestDirections.push_back(direction);
            } else if (manhattanDistance == minManhattanDistance) {
                bestDirections.push_back(direction);
            }
        }

        if (!bestDirections.empty()) {
            return bestDirections[Random::getInstance()->randomIndex(bestDirections.size())];
        }

        return ghost.getDirection();
    }

    if (ghostType == GhostType::Chaser) {
        std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

        if (possibleDirections.size() == 1)
            return possibleDirections[0];

        int minManhattanDistance = std::numeric_limits<int>::max();
        std::vector<Direction> bestDirections;

        const int pacTileX = getTileX(_pacman->getX());
        const int pacTileY = getTileY(_pacman->getY());

        const int ghostTileX = getTileX(ghost.getX());
        const int ghostTileY = getTileY(ghost.getY());

        for (const auto& direction : possibleDirections) {
            std::pair<int, int> nextGhostTile = getTileInDirection(ghostTileX, ghostTileY, direction);

            int manhattanDistance = getManhattanDistance(nextGhostTile.first, nextGhostTile.second, pacTileX, pacTileY);

            if (manhattanDistance < minManhattanDistance) {
                minManhattanDistance = manhattanDistance;
                bestDirections.clear();
                bestDirections.push_back(direction);
            } else if (manhattanDistance == minManhattanDistance) {
                bestDirections.push_back(direction);
            }
        }

        if (!bestDirections.empty()) {
            return bestDirections[Random::getInstance()->randomIndex(bestDirections.size())];
        }

        return ghost.getDirection();
    }

    return ghost.getDirection();
}

Direction World::getNextFearedGhostDirection(const Ghost& ghost) const {
    std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

    if (possibleDirections.size() == 1)
        return possibleDirections[0];

    int maxManhattanDistance = -1;
    std::vector<Direction> bestDirections;

    const int pacTileX = getTileX(_pacman->getX());
    const int pacTileY = getTileY(_pacman->getY());

    const int ghostTileX = getTileX(ghost.getX());
    const int ghostTileY = getTileY(ghost.getY());

    for (const auto& direction : possibleDirections) {
        std::pair<int, int> nextGhostTile = getTileInDirection(ghostTileX, ghostTileY, direction);

        int manhattanDistance = getManhattanDistance(nextGhostTile.first, nextGhostTile.second, pacTileX, pacTileY);

        if (manhattanDistance > maxManhattanDistance) {
            maxManhattanDistance = manhattanDistance;
            bestDirections.clear();
            bestDirections.push_back(direction);
        } else if (manhattanDistance == maxManhattanDistance) {
            bestDirections.push_back(direction);
        }
    }

    if (!bestDirections.empty()) {
        return bestDirections[Random::getInstance()->randomIndex(bestDirections.size())];
    }

    return ghost.getDirection();
}

} // namespace logic