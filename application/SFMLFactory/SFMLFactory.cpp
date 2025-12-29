#include "SFMLFactory.h"

#include <Views/CoinView.h>
#include <Views/FruitView.h>
#include <Views/GhostView.h>
#include <Views/PacmanView.h>
#include <Views/WallView.h>

namespace application {

std::vector<std::shared_ptr<EntityView>> SFMLFactory::getViews() const { return _views; }

void SFMLFactory::setScoreObserver(const std::shared_ptr<logic::Observer>& observer) { _scoreObserver = observer; }

// Creates the pacman entity, attaches score observer and PacmanView then returns it.
std::unique_ptr<logic::Pacman> SFMLFactory::createPacman(float x, float y, float width, float height, int spawnTileX,
                                                         int spawnTileY) {
    std::unique_ptr<logic::Pacman> pacman =
        std::make_unique<logic::Pacman>(x, y, width, height, spawnTileX, spawnTileY);

    if (_scoreObserver)
        pacman->addObserver(_scoreObserver);

    const std::shared_ptr<PacmanView> view = std::make_shared<PacmanView>(*pacman);
    _views.push_back(view);
    pacman->addObserver(view);

    return pacman;
}

// Creates the wall entity, attaches WallView then returns it.
std::unique_ptr<logic::Wall> SFMLFactory::createWall(float x, float y, float width, float height) {
    std::unique_ptr<logic::Wall> wall = std::make_unique<logic::Wall>(x, y, width, height);

    const std::shared_ptr<WallView> view = std::make_shared<WallView>(*wall);
    _views.push_back(view);
    wall->addObserver(view);

    return wall;
}

// Creates the coin entity, attaches score observer and CoinView then returns it.
std::unique_ptr<logic::Coin> SFMLFactory::createCoin(float x, float y, float width, float height) {
    std::unique_ptr<logic::Coin> coin = std::make_unique<logic::Coin>(x, y, width, height);

    if (_scoreObserver)
        coin->addObserver(_scoreObserver);

    const std::shared_ptr<CoinView> view = std::make_shared<CoinView>(*coin);
    _views.push_back(view);
    coin->addObserver(view);

    return coin;
}

// Creates the fruit entity, attaches score observer and FruitView then returns it.
std::unique_ptr<logic::Fruit> SFMLFactory::createFruit(float x, float y, float width, float height) {
    std::unique_ptr<logic::Fruit> fruit = std::make_unique<logic::Fruit>(x, y, width, height);

    if (_scoreObserver)
        fruit->addObserver(_scoreObserver);

    const std::shared_ptr<FruitView> view = std::make_shared<FruitView>(*fruit);
    _views.push_back(view);
    fruit->addObserver(view);

    return fruit;
}

// Creates the ghost entity, attaches GhostView then returns it.
std::unique_ptr<logic::Ghost> SFMLFactory::createGhost(float x, float y, float width, float height, int spawnTileX,
                                                       int spawnTileY, logic::GhostType ghostType) {
    std::unique_ptr<logic::Ghost> ghost =
        std::make_unique<logic::Ghost>(x, y, width, height, spawnTileX, spawnTileY, ghostType);

    const std::shared_ptr<GhostView> view = std::make_shared<GhostView>(*ghost);
    _views.push_back(view);
    ghost->addObserver(view);

    return ghost;
}

} // namespace application