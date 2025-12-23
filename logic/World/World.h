#ifndef WORLD_H
#define WORLD_H
#include "Entities/Coin.h"
#include "Entities/Wall.h"

#include <AbstractFactory/AbstractFactory.h>
#include <Entities/Pacman.h>
#include <memory>
#include <string>
#include <vector>

namespace logic {

enum class Actions { Up, Down, Left, Right };

class World {
public:
    World(AbstractFactory& factory);
    ~World() = default;

    void handleAction(Actions action) const;
    void update(float deltaTime);
    void loadMap(const std::vector<std::string>& map);
    [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& getWalls() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Coin>>& getCoins() const;
    [[nodiscard]] Pacman& getPacman() const;

private:
    [[nodiscard]] bool isColliding(const Bounds& A, const Bounds& B) const;
    [[nodiscard]] bool willCollideWithWalls(const Bounds& A) const;

    AbstractFactory& _factory;

    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<std::unique_ptr<Coin>> _coins;
    std::unique_ptr<Pacman> _pacman;
};

} // namespace logic

#endif // WORLD_H
