#ifndef WORLD_H
#define WORLD_H
#include "Entities/Wall.h"

#include <memory>
#include <string>
#include <vector>

namespace logic {

class World {
public:
    World() = default;
    ~World() = default;

    void loadMap(const std::vector<std::string>& map);
    [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& getWalls() const;

private:
    std::vector<std::unique_ptr<Wall>> _walls;
};

} // namespace logic

#endif // WORLD_H
