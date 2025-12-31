#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "EntityModel.h"

namespace logic::entities {

/**
 * @brief Base class for collectable entities like Coins and Fruits
 *
 * The class has a getter for the _isCollected flag and a virtual collect() method that derived classes must implement
 * to change this _isCollected flag.
 */
class Collectable : public EntityModel {
public:
    /**
     * @brief Constructs a new Collectable instance.
     * @param x The X coordinate of the entity.
     * @param y The Y coordinate of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    Collectable(float x, float y, float width, float height);
    virtual ~Collectable() = default;

    /**
     * @brief Returns whether this collectable has been collected.
     * @return True if collected, false otherwise.
     */
    [[nodiscard]] bool isCollected() const;

    /**
     * @brief Collects this entity.
     *
     * Derived classes must implement this method to handle collection logic.
     */
    virtual void collect() = 0;

protected:
    bool _isCollected = false;
};

} // namespace logic

#endif // COLLECTABLE_H
