#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H
#include "Util/Structs.h"

#include <Observer/Subject.h>

namespace logic::entities {

/**
 * @brief Base class for all game entities that provides position, size and a method to get the bounding box.
 *
 * The class has getters for position, width, height and bounding box for collision detection.
 * The position (x, y) of an entity is the center of the entity.
 *
 * Implements the Observer/Subject design pattern.
 */
class EntityModel : public Subject {
public:
    virtual ~EntityModel() = default;

    /**
     * @brief Returns the X coordinate of the entity.
     */
    [[nodiscard]] float getX() const;

    /**
     * @brief Returns the Y coordinate of the entity.
     */
    [[nodiscard]] float getY() const;

    /**
     * @brief Returns the width of the entity.
     */
    [[nodiscard]] float getWidth() const;

    /**
     * @brief Returns the height of the entity.
     */
    [[nodiscard]] float getHeight() const;

    /**
     * @brief Returns the bounding box of the entity.
     */
    [[nodiscard]] util::Bounds getBounds() const;

protected:
    EntityModel(float x, float y, float width, float height);
    float _x = 0;
    float _y = 0;
    float _width = 0;
    float _height = 0;
};

} // namespace logic::entities

#endif // ENTITYMODEL_H
