#include "World.h"

namespace logic {

void World::loadMap(const std::vector<std::string>& map) {
    _walls.clear();
    if (map.empty())
        return;

    const int rows = map.size();
    const int cols = map[0].size();
    const float cellWidth = 2.0f / cols;
    const float cellHeight = 2.0f / rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] != '#')
                continue;

            float x = -1.0f + cellWidth * (j + 0.5f);
            float y = 1.0f - cellHeight * (i + 0.5f);
            _walls.push_back(std::make_unique<Wall>(x, y, cellWidth, cellHeight));
        }
    }
}
const std::vector<std::unique_ptr<Wall>>& World::getWalls() const { return _walls; }

} // namespace logic