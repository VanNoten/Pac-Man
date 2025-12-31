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

    /**
     * @brief Creates a pacman entity, attaches score observer and PacmanView then returns a pointer to it.
     */
    std::unique_ptr<logic::entities::Pacman> createPacman(float x, float y, float width, float height, int spawnTileX,
                                                          int spawnTileY) override;

    /**
     * @brief Creates a wall entity, attaches WallView then returns a pointer to it.
     */
    std::unique_ptr<logic::entities::Wall> createWall(float x, float y, float width, float height) override;

    /**
     * @brief Creates a coin entity, attaches score observer and CoinView then returns a pointer to it.
     */
    std::unique_ptr<logic::entities::Coin> createCoin(float x, float y, float width, float height) override;

    /**
     * @brief Creates a fruit entity, attaches score observer and FruitView then returns a pointer to it.
     */
    std::unique_ptr<logic::entities::Fruit> createFruit(float x, float y, float width, float height) override;

    /**
     * @brief Creates a ghost entity, attaches GhostView then returns a pointer to it.
     */
    std::unique_ptr<logic::entities::Ghost> createGhost(float x, float y, float width, float height, int spawnTileX,
                                                        int spawnTileY, logic::entities::GhostType ghostType) override;

private:
    std::vector<std::shared_ptr<EntityView>> _views;

    std::shared_ptr<logic::Observer> _scoreObserver;
};

} // namespace application

#endif // SFMLFACTORY_H
