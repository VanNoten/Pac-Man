#include "World.h"

namespace logic {

void World::handleAction(Actions action) const {
    switch (action) {
    case Actions::UpArrow:
        _pacman->setDirection(Direction::UP);
        break;
    case Actions::DownArrow:
        _pacman->setDirection(Direction::DOWN);
        break;
    case Actions::LeftArrow:
        _pacman->setDirection(Direction::LEFT);
        break;
    case Actions::RightArrow:
        _pacman->setDirection(Direction::RIGHT);
        break;
    default:
        break;
    }
}

void World::update(const float deltaTime) { _pacman->update(deltaTime); }

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

    if (_pacman) {
        _pacman->setSize(cell * 0.9f);
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const float x = originX + cell * (c + 0.5f);
            const float y = originY - cell * (r + 0.5f);

            switch (map[r][c]) {
            case '#':
                _walls.push_back(std::make_unique<Wall>(x, y, cell, cell));
                break;
            case '@':
                _pacman = std::make_unique<Pacman>(x, y);
                break;
            default:
                break;
            }
        }
    }
}

const std::vector<std::unique_ptr<Wall>>& World::getWalls() const { return _walls; }

Pacman& World::getPacman() const { return *_pacman; }

} // namespace logic