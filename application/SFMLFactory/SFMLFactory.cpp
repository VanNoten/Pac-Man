#include "SFMLFactory.h"

#include <Views/CoinView.h>
#include <Views/FruitView.h>
#include <Views/GhostView.h>
#include <Views/PacmanView.h>
#include <Views/WallView.h>

namespace application {

using namespace logic::entities;
using namespace application::views;

std::vector<std::shared_ptr<EntityView>> SFMLFactory::getViews() const { return _views; }

void SFMLFactory::setScoreObserver(const std::shared_ptr<logic::Observer>& observer) { _scoreObserver = observer; }

std::unique_ptr<Pacman> SFMLFactory::createPacman(float x, float y, float width, float height, int spawnTileX,
                                                  int spawnTileY) {
    std::unique_ptr<Pacman> pacman = std::make_unique<Pacman>(x, y, width, height, spawnTileX, spawnTileY);

    if (_scoreObserver)
        pacman->addObserver(_scoreObserver);

    const std::shared_ptr<PacmanView> view = std::make_shared<PacmanView>(*pacman);
    _views.push_back(view);
    pacman->addObserver(view);

    return pacman;
}

std::unique_ptr<Wall> SFMLFactory::createWall(float x, float y, float width, float height) {
    std::unique_ptr<Wall> wall = std::make_unique<Wall>(x, y, width, height);

    const std::shared_ptr<WallView> view = std::make_shared<WallView>(*wall);
    _views.push_back(view);
    wall->addObserver(view);

    return wall;
}

std::unique_ptr<Coin> SFMLFactory::createCoin(float x, float y, float width, float height) {
    std::unique_ptr<Coin> coin = std::make_unique<Coin>(x, y, width, height);

    if (_scoreObserver)
        coin->addObserver(_scoreObserver);

    const std::shared_ptr<CoinView> view = std::make_shared<CoinView>(*coin);
    _views.push_back(view);
    coin->addObserver(view);

    return coin;
}

std::unique_ptr<Fruit> SFMLFactory::createFruit(float x, float y, float width, float height) {
    std::unique_ptr<Fruit> fruit = std::make_unique<Fruit>(x, y, width, height);

    if (_scoreObserver)
        fruit->addObserver(_scoreObserver);

    const std::shared_ptr<FruitView> view = std::make_shared<FruitView>(*fruit);
    _views.push_back(view);
    fruit->addObserver(view);

    return fruit;
}

std::unique_ptr<Ghost> SFMLFactory::createGhost(float x, float y, float width, float height, int spawnTileX,
                                                int spawnTileY, GhostType ghostType) {
    std::unique_ptr<Ghost> ghost = std::make_unique<Ghost>(x, y, width, height, spawnTileX, spawnTileY, ghostType);

    const std::shared_ptr<GhostView> view = std::make_shared<GhostView>(*ghost);
    _views.push_back(view);
    ghost->addObserver(view);

    return ghost;
}

} // namespace application