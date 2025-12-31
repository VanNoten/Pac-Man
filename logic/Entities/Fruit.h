#ifndef FRUIT_H
#define FRUIT_H
#include "Collectable.h"

namespace logic::entities {

/**
 * @brief Collectable fruit entity that can be collected by pacman for points and fears ghosts.
 */
class Fruit : public Collectable {
public:
    /**
     * @brief Constructs a new Fruit instance.
     * @param x The X coordinate of the entity.
     * @param y The Y coordinate of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    Fruit(float x, float y, float width, float height);

    /**
     * @brief Collects the fruit.
     *
     * Sends a FruitCollected event to all attached observers.
     * Sets the _isCollected flag to true.
     */
    void collect() override;
};

} // namespace logic::entities

#endif // FRUIT_H
