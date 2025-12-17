#ifndef PACMAN_H
#define PACMAN_H
#include "EntityModel.h"

namespace logic {

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Pacman : public EntityModel {
public:
    Pacman(float x, float y);
    void update(float deltaTime) override;
    [[nodiscard]] float getWidth() const override;
    [[nodiscard]] float getHeight() const override;
    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;
    void setSize(float size);

private:
    Direction _direction = Direction::RIGHT;
    float _size = 0.08f;
    float _speed = 10.0f;
};

} // namespace logic

#endif // PACMAN_H
