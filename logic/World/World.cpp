#include "World.h"

namespace logic {

void World::handleAction(Actions action) const {
    switch (action) {
    case Actions::UpArrow:
        _pacman->setWantedDirection(Direction::UP);
        break;
    case Actions::DownArrow:
        _pacman->setWantedDirection(Direction::DOWN);
        break;
    case Actions::LeftArrow:
        _pacman->setWantedDirection(Direction::LEFT);
        break;
    case Actions::RightArrow:
        _pacman->setWantedDirection(Direction::RIGHT);
        break;
    default:
        break;
    }
}

void World::update(const float deltaTime) {
    Direction wantedDirection = _pacman->getWantedDirection();
    Direction currentDirection = _pacman->getDirection();
    _pacman->setDirection(wantedDirection);

    if (willCollideWithWalls(_pacman->getNextBounds(deltaTime))) {
        _pacman->setDirection(currentDirection);
    }

    if (!willCollideWithWalls(_pacman->getNextBounds(deltaTime))) {
        _pacman->update(deltaTime);
    }
}

void World::loadMap(const std::vector<std::string>& map) {
    _walls.clear();
    if (map.empty())
        return;

    const int rows = map.size();
    const int cols = map[0].size();

    const float cell = 2.0f / std::max(cols, rows);

    const float totalWidth = cell * cols;
    const float totalHeight = cell * rows;

    const float originX = -totalWidth * 0.5f;
    const float originY = totalHeight * 0.5f;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const float x = originX + cell * (c + 0.5f);
            const float y = originY - cell * (r + 0.5f);

            switch (map[r][c]) {
            case '#':
                _walls.push_back(std::make_unique<Wall>(x, y, cell, cell));
                break;
            case '@':
                _pacman = std::make_unique<Pacman>(x, y, cell * 0.9f, cell * 0.9f);
                break;
            default:
                break;
            }
        }
    }
}

const std::vector<std::unique_ptr<Wall>>& World::getWalls() const { return _walls; }

Pacman& World::getPacman() const { return *_pacman; }

bool World::isColliding(const Bounds& A, const Bounds& B) const {
    return (A.left < B.right && A.right > B.left) && (A.top < B.bottom && A.bottom > B.top);
}

bool World::willCollideWithWalls(const Bounds& A) const {
    for (const auto& wall : _walls) {
        if (isColliding(A, wall->getBounds())) {
            return true;
        }
    }
    return false;
}

} // namespace logic