#ifndef ABSTRACTFACTORY_H
#define ABSTRACTFACTORY_H
#include <Entities/Coin.h>
#include <Entities/Ghost.h>
#include <Entities/Pacman.h>
#include <Entities/Wall.h>
#include <memory>

namespace logic {

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<Pacman> createPacman(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<Wall> createWall(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<Coin> createCoin(float x, float y, float width, float height) = 0;
    virtual std::unique_ptr<Ghost> createGhost(float x, float y, float width, float height, GhostType ghostType) = 0;
};

} // namespace logic

#endif // ABSTRACTFACTORY_H
