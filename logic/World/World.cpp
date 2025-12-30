#include "World.h"

#include <Util/Constants.h>
#include <Util/Random.h>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace logic {

World::World(AbstractFactory& factory) : _factory(factory) {}

void World::handleAction(const Actions action) const {
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

        // Handle pacman-ghost collision, if ghost is feared -> pacman eats ghost, else pacman dies
        if (isColliding(_pacman->getBounds(), ghost->getBounds())) {
            if (ghost->getIsFeared()) {
                const int tileX = ghost->getSpawnTileX();
                const int tileY = ghost->getSpawnTileY();
                const float tileCenterX = getTileCenterX(tileX);
                const float tileCenterY = getTileCenterY(tileY);
                ghost->setPosition(tileCenterX, tileCenterY); // Ghost teleports back to its spawn tile
                ghost->setIsFeared(false);
                ghost->setActive(true);
                _pacman->eatGhost();
            } else {
                handlePacmanDeath();
            }
        }
    }

    // Handle pacman-coin collection
    for (const auto& coin : _coins) {
        if (!coin->isCollected() && isColliding(_pacman->getBounds(), coin->getBounds())) {
            coin->collect();
            _collectablesLeft--;
            if (_collectablesLeft <= 0) {
                notify(EventType::LevelCleared); // LevelCleared event sent to Score observer
                _isGameVictory = true;
            }
        }
    }

    // Handle pacman-fruit collection
    for (const auto& fruit : _fruits) {
        if (!fruit->isCollected() && isColliding(_pacman->getBounds(), fruit->getBounds())) {
            fruit->collect();
            _collectablesLeft--;
            if (_collectablesLeft <= 0) {
                notify(EventType::LevelCleared); // LevelCleared event sent to Score observer
                _isGameVictory = true;
            }

            fearGhosts();
        }
    }
}

void World::loadMap(const std::vector<std::string>& map, const int pacmanLives, const int currentLevel) {
    _walls.clear();
    if (map.empty())
        return;

    _map = map;

    const int rows = map.size();
    const int cols = map[0].size();

    // Calculate the size of one cell for coordinate system bounded by [-1, 1]
    _cell = 2.0f / std::max(cols, rows);

    // Max total width and height is 2
    const float totalWidth = _cell * cols;
    const float totalHeight = _cell * rows;

    _originX = -totalWidth * 0.5f; // Left edge of the map
    _originY = totalHeight * 0.5f; // Top edge of the map

    // Read through the map and create the correct entity depending on the character read
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // X coordinate is in the center of a cell
            // Formula: Left edge of map + (cell size * current column) + (cell size * 0.5)
            const float x = _originX + _cell * (c + 0.5f);

            // Y coordinate is in the center of a cell
            // Formula: Top edge of map - (cell size * current row) - (cell size * 0.5)
            const float y = _originY - _cell * (r + 0.5f);

            switch (map[r][c]) {
            case '#':
                _walls.push_back(_factory.createWall(x, y, _cell, _cell));
                break;
            case '@':
                _pacman = _factory.createPacman(x, y, _cell * 0.9f, _cell * 0.9f, c, r);
                _pacman->setLives(pacmanLives);
                break;
            case '.':
                _coins.push_back(_factory.createCoin(x, y, _cell * 0.2f, _cell * 0.2f));
                _collectablesLeft += 1;
                break;
            case 'F':
                _fruits.push_back(_factory.createFruit(x, y, _cell * 0.6f, _cell * 0.6f));
                _collectablesLeft += 1;
                break;
            // Create the four ghosts and push the corresponding timers
            case '1': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::Locked);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GameConstants::GHOST_1_DELAY);
            } break;
            case '2': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::AheadChaser1);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GameConstants::GHOST_2_DELAY);
            } break;
            case '3': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::AheadChaser2);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GameConstants::GHOST_3_DELAY);
            } break;
            case '4': {
                std::unique_ptr<Ghost> ghost =
                    _factory.createGhost(x, y, _cell * 0.9f, _cell * 0.9f, c, r, GhostType::Chaser);
                ghost->setActive(false);
                _ghosts.push_back(std::move(ghost));
                _ghostDelayTimers.push_back(GameConstants::GHOST_4_DELAY);
            } break;
            default:
                break;
            }
        }
    }

    _currentLevel = currentLevel;
    setSpeedsForLevel(); // Set the right speeds and durations for the current level
}

int World::getCurrentLevel() const { return _currentLevel; }

bool World::getIsGameOver() const { return _isGameOver; }

bool World::getIsGameVictory() const { return _isGameVictory; }

int World::getPacmanLives() const {
    if (_pacman) {
        return _pacman->getLives();
    }
    return 0;
}

void World::handlePacmanMovement(const float deltaTime) const {
    if (!_pacman)
        return;

    // Calculate the amount of distance to move using deltaTime
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

    // Reverse direction changes are allowed instantly for better responsiveness
    if (isReverseDirection) {
        _pacman->setDirection(wantedDirection);
        currentDirection = wantedDirection;
    }

    const int tileX = getTileX(x);
    const int tileY = getTileY(y);
    const float centerX = getTileCenterX(tileX);
    const float centerY = getTileCenterY(tileY);

    // Calculate squared distance from pacman to the center of the current tile
    // (using squared distance avoids expensive sqrt calculation)
    float distanceToCenterTile = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);

    // If close enough to the center we allow pacman to change direction if possible
    if (distanceToCenterTile < moveDistance * moveDistance + 1e-4f) {
        if (wantedDirection != currentDirection) {
            // Get the tile pacman wants to go to and only allow direction change if that tile is not a wall
            std::pair<int, int> nextTile = getTileInDirection(tileX, tileY, wantedDirection);

            if (!isWallAtTile(nextTile.first, nextTile.second)) {
                _pacman->setPosition(centerX, centerY); // Snap pacman to the center of the tile
                _pacman->setDirection(wantedDirection);
                currentDirection = wantedDirection;
            }
        }

        // Check if tile pacman is going to is a wall, if it is then set pacman to the center of that tile and return
        std::pair<int, int> tileInfront = getTileInDirection(tileX, tileY, currentDirection);

        if (isWallAtTile(tileInfront.first, tileInfront.second)) {
            _pacman->setPosition(centerX, centerY);
            return;
        }
    }

    // Calculate how much pacman needs to move in x and y and move pacman
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
    // Calculate the amount of distance to move using deltaTime
    const float speed = ghost.getSpeed();
    const float moveDistance = speed * deltaTime;

    const float x = ghost.getX();
    const float y = ghost.getY();
    const int tileX = getTileX(x);
    const int tileY = getTileY(y);
    const float centerX = getTileCenterX(tileX);
    const float centerY = getTileCenterY(tileY);

    Direction currentDirection = ghost.getDirection();

    // Check if ghost has already made a direction change decision on its current tile
    const bool isNewTile = tileX != ghost.getLastDecisionTileX() || tileY != ghost.getLastDecisionTileY();

    // Calculate squared distance from ghost to the center of the current tile
    // (using squared distance avoids expensive sqrt calculation)
    float distanceToCenterTile = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);

    // If ghost is close enough to tile center and has not made a direction change decision yet, we allow ghost to
    // change direction if possible
    if (distanceToCenterTile < moveDistance * moveDistance + 1e-4f && isNewTile) {
        ghost.setLastDecisionTile(tileX, tileY);

        Direction nextDirection;
        // If ghost is not feared it will try to minimize manhattan distance from pacman, else maximize manhattan
        // distance
        if (!ghost.getIsFeared()) {
            nextDirection = getNextGhostDirection(ghost);
        } else {
            nextDirection = getNextFearedGhostDirection(ghost);
        }

        ghost.setDirection(nextDirection);
        // Snap ghost to center if direction is different to previous direction
        if (currentDirection != nextDirection) {
            ghost.setPosition(centerX, centerY);
            currentDirection = nextDirection;
        }

        // Check if tile ghost is going to is a wall, if it is then set ghost to the center of that tile and return
        std::pair<int, int> tileInfront = getTileInDirection(tileX, tileY, currentDirection);

        if (isWallAtTile(tileInfront.first, tileInfront.second)) {
            ghost.setPosition(centerX, centerY);
            return;
        }
    }

    // Calculate how much ghost needs to move in x and y and move ghost
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
    // Go through all ghost delay timers and activate each ghost after their corresponding delay
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
    _fearedTimer = std::max(GameConstants::BASE_FEARED_DURATION -
                                GameConstants::FEARED_DURATION_DECREASE_PER_LEVEL * (_currentLevel - 1),
                            GameConstants::MIN_FEARED_DURATION);
    _ghostsAreFeared = true;

    for (const auto& ghost : _ghosts) {
        if (!ghost->getIsFeared()) {
            const Direction reverseDirection = getReverseDirection(ghost->getDirection());
            const int ghostTileX = getTileX(ghost->getX());
            const int ghostTileY = getTileY(ghost->getY());
            std::pair<int, int> reverseTile = getTileInDirection(ghostTileX, ghostTileY, reverseDirection);
            if (!isWallAtTile(reverseTile.first, reverseTile.second)) {
                ghost->setDirection(reverseDirection);
                ghost->setLastDecisionTile(-1, -1); // force wall collision check after reversal
            }
        }

        ghost->setIsFeared(true);
    }
}

void World::handlePacmanDeath() {
    _pacman->die();

    if (_pacman->getLives() <= 0) {
        notify(EventType::GameOver);
        _isGameOver = true;
        return;
    }

    resetGhostsAndPacman();
}

void World::setSpeedsForLevel() {
    const float newGhostSpeed =
        std::min(GameConstants::BASE_GHOST_SPEED + (GameConstants::SPEED_INCREASE_PER_LEVEL * (_currentLevel - 1)),
                 GameConstants::MAX_GHOST_SPEED);

    const float newFearedGhostSpeed = std::min(GameConstants::BASE_FEARED_GHOST_SPEED +
                                                   (GameConstants::SPEED_INCREASE_PER_LEVEL * (_currentLevel - 1)),
                                               GameConstants::MAX_FEARED_GHOST_SPEED);

    for (const auto& ghost : _ghosts) {
        ghost->setSpeeds(newGhostSpeed, newFearedGhostSpeed);
    }
}

void World::resetGhostsAndPacman() {
    const int pacSpawnTileX = _pacman->getSpawnTileX();
    const int pacSpawnTileY = _pacman->getSpawnTileY();
    _pacman->setPosition(getTileCenterX(pacSpawnTileX), getTileCenterY(pacSpawnTileY));
    _pacman->setDirection(Direction::RIGHT);

    for (const auto& ghost : _ghosts) {
        const int spawnTileX = ghost->getSpawnTileX();
        const int spawnTileY = ghost->getSpawnTileY();
        ghost->setPosition(getTileCenterX(spawnTileX), getTileCenterY(spawnTileY));
        ghost->setIsFeared(false);
    }

    _ghostsAreFeared = false;
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
    const GhostType ghostType = ghost.getGhostType();
    std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

    if (possibleDirections.size() == 1)
        return possibleDirections[0];

    // For the locked ghost type it has a 50% chance of switching directions at an intersection or continuing with the
    // current locked direction
    if (ghostType == GhostType::Locked) {
        if (Random::getInstance().chance(0.5)) {
            std::vector<Direction> filteredDirections;
            for (const auto direction : possibleDirections) {
                if (direction != ghost.getDirection()) {
                    filteredDirections.push_back(direction);
                }
            }

            if (!filteredDirections.empty()) {
                return filteredDirections[Random::getInstance().randomIndex(filteredDirections.size())];
            }
        }

        // Check if ghost can continue in locked direction
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

        // If current locked direction is not possible just pick a random possible direction
        return possibleDirections[Random::getInstance().randomIndex(possibleDirections.size())];
    }

    // AheadChaser ghost type tries to minimize the manhattan distance to the tile infront of pacman
    if (ghostType == GhostType::AheadChaser1 || ghostType == GhostType::AheadChaser2) {
        std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

        if (possibleDirections.size() == 1)
            return possibleDirections[0];

        // Get the smallest manhattan distance(s) out of all possible directions
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

        // If there are multiple directions with the same manhattan distance just pick a random one
        if (!bestDirections.empty()) {
            return bestDirections[Random::getInstance().randomIndex(bestDirections.size())];
        }

        return ghost.getDirection();
    }

    // Chaser ghost type tries to minimize the manhattan distance to the tile pacman is on
    if (ghostType == GhostType::Chaser) {
        std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

        if (possibleDirections.size() == 1)
            return possibleDirections[0];

        // Get the smallest manhattan distance(s) out of all possible directions
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

        // If there are multiple directions with the same manhattan distance just pick a random one
        if (!bestDirections.empty()) {
            return bestDirections[Random::getInstance().randomIndex(bestDirections.size())];
        }

        return ghost.getDirection();
    }

    return ghost.getDirection();
}

Direction World::getNextFearedGhostDirection(const Ghost& ghost) const {
    std::vector<Direction> possibleDirections = getPossibleDirections(ghost);

    if (possibleDirections.size() == 1)
        return possibleDirections[0];

    // Get the largest manhattan distance(s) out of all possible directions
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

    // If there are multiple directions with the same manhattan distance just pick a random one
    if (!bestDirections.empty()) {
        return bestDirections[Random::getInstance().randomIndex(bestDirections.size())];
    }

    return ghost.getDirection();
}

} // namespace logic