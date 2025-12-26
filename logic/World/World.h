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
    [[nodiscard]] const std::vector<std::unique_ptr<Ghost>>& getGhosts() const;
    [[nodiscard]] Pacman& getPacman() const;

private:
    void handlePacmanMovement(float deltaTime) const;
    void handleGhostMovement(Ghost& ghost, float deltaTime) const;
    [[nodiscard]] static bool isColliding(const Bounds& A, const Bounds& B);
    [[nodiscard]] float getTileCenterX(int tileX) const;
    [[nodiscard]] float getTileCenterY(int tileY) const;
    [[nodiscard]] int getTileX(float x) const;
    [[nodiscard]] int getTileY(float y) const;
    [[nodiscard]] static std::pair<int, int> getTileInDirection(int tileX, int tileY, Direction direction);
    [[nodiscard]] bool isWallAtTile(int tileX, int tileY) const;
    [[nodiscard]] static int getManhattanDistance(int fromTileX, int fromTileY, int toTileX, int toTileY);
    [[nodiscard]] std::vector<Direction> getPossibleDirections(const Ghost& ghost) const;
    [[nodiscard]] Direction getNextGhostDirection(const Ghost& ghost) const;

    std::vector<std::string> _map = {};
    float _originX, _originY, _cell;
    AbstractFactory& _factory;

    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<std::unique_ptr<Coin>> _coins;
    std::vector<std::unique_ptr<Ghost>> _ghosts;
    std::unique_ptr<Pacman> _pacman;
};

} // namespace logic

#endif // WORLD_H
