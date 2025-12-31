#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <Entities/Coin.h>
#include <Entities/Fruit.h>
#include <Entities/Ghost.h>
#include <Entities/Pacman.h>
#include <Entities/Wall.h>
#include <memory>

namespace logic {

/**
 * @brief Abstract interface for creating game entities.
 *
 * Implements the Abstract Factory design pattern so the logic library does not have any knowledge of how the game is
 * represented.
 */
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<entities::Pacman> createPacman(float x, float y, float width, float height, int spawnTileX,
                                                           int spawnTileY) = 0;
    virtual std::unique_ptr<entities::Wall> createWall(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<entities::Coin> createCoin(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<entities::Fruit> createFruit(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<entities::Ghost> createGhost(float x, float y, float width, float height, int spawnTileX,
                                                         int spawnTileY, entities::GhostType ghostType) = 0;
};

} // namespace logic

#endif // ABSTRACTFACTORY_H
