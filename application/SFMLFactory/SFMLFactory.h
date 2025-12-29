#ifndef SFMLFACTORY_H
#define SFMLFACTORY_H

#include <AbstractFactory/AbstractFactory.h>
#include <Views/EntityView.h>

namespace application {

/**
 * @brief Concrete factory that creates game entities and attaches entity views and observers.
 *
 * Implements the Abstract Factory design pattern so the World class has no knowledge of representation logic.
 */
class SFMLFactory : public logic::AbstractFactory {
public:
    /**
     * @brief Returns all entity views.
     */
    [[nodiscard]] std::vector<std::shared_ptr<EntityView>> getViews() const;

    /**
     * @brief Sets score observer variable so it can be attached to entities that need it.
     * @param observer Observer to be set.
     */
    void setScoreObserver(const std::shared_ptr<logic::Observer>& observer);

    std::unique_ptr<logic::Pacman> createPacman(float x, float y, float width, float height, int spawnTileX,
                                                int spawnTileY) override;
    std::unique_ptr<logic::Wall> createWall(float x, float y, float width, float height) override;
    std::unique_ptr<logic::Coin> createCoin(float x, float y, float width, float height) override;
    std::unique_ptr<logic::Fruit> createFruit(float x, float y, float width, float height) override;
    std::unique_ptr<logic::Ghost> createGhost(float x, float y, float width, float height, int spawnTileX,
                                              int spawnTileY, logic::GhostType ghostType) override;

private:
    std::vector<std::shared_ptr<EntityView>> _views;

    std::shared_ptr<logic::Observer> _scoreObserver;
};

} // namespace application

#endif // SFMLFACTORY_H
