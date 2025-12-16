#ifndef WALL_H
#define WALL_H
#include "EntityModel.h"

namespace logic {

class Wall : public EntityModel {
public:
    Wall(float x, float y, float width, float height);
    void update(float deltaTime) override {}
    [[nodiscard]] float getWidth() const override;
    [[nodiscard]] float getHeight() const override;

private:
    float _width;
    float _height;
};

} // namespace logic

#endif // WALL_H
