#ifndef PACMAN_H
#define PACMAN_H
#include "EntityModel.h"
#include "Util/Structs.h"

namespace logic {

class Pacman : public EntityModel {
public:
    Pacman(float x, float y, float width, float height);
    void update(float deltaTime) override;
    [[nodiscard]] Bounds getNextBounds(float deltaTime) const;
    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;
    void setWantedDirection(Direction direction);
    [[nodiscard]] Direction getWantedDirection() const;

private:
    Direction _direction = Direction::RIGHT;
    Direction _wantedDirection = Direction::RIGHT;
    float _speed = 0.3f;
};

} // namespace logic

#endif // PACMAN_H
