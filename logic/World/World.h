#ifndef WORLD_H
#define WORLD_H
#include "Entities/Wall.h"

#include <Entities/Pacman.h>
#include <memory>
#include <string>
#include <vector>

namespace logic {

class World {
public:
    World() = default;
    ~World() = default;

    void update(float deltaTime);
    void loadMap(const std::vector<std::string>& map);
    [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& getWalls() const;
    [[nodiscard]] Pacman& getPacman() const;

private:
    std::vector<std::unique_ptr<Wall>> _walls;
    std::unique_ptr<Pacman> _pacman;
};

} // namespace logic

#endif // WORLD_H
