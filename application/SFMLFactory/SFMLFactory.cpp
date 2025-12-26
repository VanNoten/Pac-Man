#include "SFMLFactory.h"

namespace application {

void SFMLFactory::setScoreObserver(const std::shared_ptr<logic::Observer>& observer) { _scoreObserver = observer; }

std::unique_ptr<logic::Pacman> SFMLFactory::createPacman(float x, float y, float width, float height) {
    return std::make_unique<logic::Pacman>(x, y, width, height);
}

std::unique_ptr<logic::Wall> SFMLFactory::createWall(float x, float y, float width, float height) {
    return std::make_unique<logic::Wall>(x, y, width, height);
}

std::unique_ptr<logic::Coin> SFMLFactory::createCoin(float x, float y, float width, float height) {
    std::unique_ptr<logic::Coin> coin = std::make_unique<logic::Coin>(x, y, width, height);

    if (_scoreObserver)
        coin->addObserver(_scoreObserver);

    return coin;
}

std::unique_ptr<logic::Ghost> SFMLFactory::createGhost(float x, float y, float width, float height,
                                                       logic::GhostType ghostType) {
    return std::make_unique<logic::Ghost>(x, y, width, height, ghostType);
}

} // namespace application