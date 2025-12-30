#ifndef COIN_H
#define COIN_H
#include "Collectable.h"

namespace logic {

/**
 * @brief Collectable coin entity that can be collected by pacman for points.
 */
class Coin : public Collectable {
public:
    /**
     * @brief Constructs a new Coin instance.
     * @param x The X coordinate of the entity.
     * @param y The Y coordinate of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    Coin(float x, float y, float width, float height);

    /**
     * @brief Collects the coin.
     *
     * Sends a CoinCollected event to all attached observers.
     * Sets the _isCollected flag to true.
     */
    void collect() override;
};

} // namespace logic

#endif // COIN_H
