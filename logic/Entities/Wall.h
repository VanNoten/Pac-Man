#ifndef WALL_H
#define WALL_H
#include "EntityModel.h"

namespace logic {

/**
 * @brief Wall entity that is created when the map is loaded.
 */
class Wall : public EntityModel {
public:
    /**
     * @brief Constructs a new Wall instance.
     * @param x The X coordinate of the entity.
     * @param y The Y coordinate of the entity.
     * @param width The width of the entity.
     * @param height The height of the entity.
     */
    Wall(float x, float y, float width, float height);
};

} // namespace logic

#endif // WALL_H
