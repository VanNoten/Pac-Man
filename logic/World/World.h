#ifndef WORLD_H
#define WORLD_H
#include "Entities/Coin.h"
#include "Entities/Wall.h"

#include <AbstractFactory/AbstractFactory.h>
#include <Entities/Pacman.h>
#include <Observer/Subject.h>
#include <memory>
#include <string>
#include <vector>

namespace logic {

enum class Actions { Up, Down, Left, Right };

class World : public Subject {
public:
    World(AbstractFactory& factory);
    ~World() = default;

    void handleAction(Actions action) const;
    void update(float deltaTime);
    void loadMap(const std::vector<std::string>& map, int pacmanLives = GameConstants::STARTING_LIVES,
                 int currentLevel = 1);
    [[nodiscard]] int getCurrentLevel() const;
    [[nodiscard]] bool getIsGameOver() const;
    [[nodiscard]] bool getIsGameVictory() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Wall>>& getWalls() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Coin>>& getCoins() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Fruit>>& getFruits() const;
    [[nodiscard]] const std::vector<std::unique_ptr<Ghost>>& getActiveGhosts() const;
    [[nodiscard]] Pacman& getPacman() const;
    void setPacmanLives(int lives) const;
    [[nodiscard]] int getPacmanLives() const;

private:
    void handlePacmanMovement(float deltaTime) const;
    void handleGhostMovement(Ghost& ghost, float deltaTime) const;
    void activateGhosts(float deltaTime);
    void fearGhosts();
    void handlePacmanDeath();
    void setSpeedsForLevel();
    void resetGhostsAndPacman();
    [[nodiscard]] static bool isColliding(const Bounds& A, const Bounds& B);
    [[nodiscard]] float getTileCenterX(int tileX) const;
    [[nodiscard]] float getTileCenterY(int tileY) const;
    [[nodiscard]] int getTileX(float x) const;
    [[nodiscard]] int getTileY(float y) const;
    [[nodiscard]] static std::pair<int, int> getTileInDirection(int tileX, int tileY, Direction direction);
    [[nodiscard]] bool isWallAtTile(int tileX, int tileY) const;
    [[nodiscard]] static int getManhattanDistance(int fromTileX, int fromTileY, int toTileX, int toTileY);
    [[nodiscard]] static Direction getReverseDirection(Direction direction);
    [[nodiscard]] std::vector<Direction> getPossibleDirections(const Ghost& ghost) const;
    [[nodiscard]] Direction getNextGhostDirection(const Ghost& ghost) const;
    [[nodiscard]] Direction getNextFearedGhostDirection(const Ghost& ghost) const;

    std::vector<std::string> _map = {};
    float _originX, _originY, _cell;
    AbstractFactory& _factory;

    std::vector<std::unique_ptr<Wall>> _walls;
    std::vector<std::unique_ptr<Coin>> _coins;
    std::vector<std::unique_ptr<Fruit>> _fruits;
    std::vector<std::unique_ptr<Ghost>> _ghosts;
    std::unique_ptr<Pacman> _pacman;

    float _fearedTimer = 0.0f;
    bool _ghostsAreFeared = false;

    std::vector<float> _ghostDelayTimers = {};
    bool _allGhostsActive = false;

    bool _isGameOver = false;
    bool _isGameVictory = false;

    int _collectablesLeft = 0;

    int _currentLevel = 1;
};

} // namespace logic

#endif // WORLD_H
