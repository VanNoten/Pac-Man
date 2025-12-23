#ifndef WORLD_H
#define WORLD_H
#include "Entities/Wall.h"

#include <Entities/Pacman.h>
#include <memory>
#include <string>
#include <vector>

namespace logic {

enum class Actions { UpArrow, DownArrow, LeftArrow, RightArrow };

class World {
public:
    World() = default;
    ~World() = default;

    void handleAction(Actions action) const;
    void update(float deltaTime);
    void loadMap(const std::vector<std::string>& map);
    [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& getWalls() const;
    [[nodiscard]] Pacman& getPacman() const;

private:
    [[nodiscard]] bool isColliding(const Bounds& A, const Bounds& B) const;
    [[nodiscard]] bool willCollideWithWalls(const Bounds& A) const;

    std::vector<std::unique_ptr<Wall>> _walls;
    std::unique_ptr<Pacman> _pacman;
};

} // namespace logic

#endif // WORLD_H
