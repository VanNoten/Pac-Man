#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H

#include <AbstractFactory/AbstractFactory.h>

namespace application {

class SFMLFactory : public logic::AbstractFactory {
public:
    void setScoreObserver(const std::shared_ptr<logic::Observer>& observer);

    std::unique_ptr<logic::Pacman> createPacman(float x, float y, float width, float height) override;
    std::unique_ptr<logic::Wall> createWall(float x, float y, float width, float height) override;
    std::unique_ptr<logic::Coin> createCoin(float x, float y, float width, float height) override;

private:
    std::shared_ptr<logic::Observer> _scoreObserver;
};

} // namespace application

#endif // SFMLFACTORY_H
