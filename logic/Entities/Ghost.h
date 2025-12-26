#ifndef GHOST_H
#define GHOST_H
#include "EntityModel.h"

namespace logic {

enum class GhostType { Locked, AheadChaser, Chaser };

class Ghost : public EntityModel {
public:
    Ghost(float x, float y, float width, float height, GhostType ghostType);
    void update(float deltaTime) override;
    void move(float x, float y);
    void setPosition(float x, float y);
    [[nodiscard]] float getSpeed() const;

    [[nodiscard]] GhostType getGhostType() const;

    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;

    void setLastDecisionTile(int tileX, int tileY);
    [[nodiscard]] int getLastDecisionTileX() const;
    [[nodiscard]] int getLastDecisionTileY() const;

private:
    Direction _direction = Direction::RIGHT;
    int _lastDecisionTileX = 0;
    int _lastDecisionTileY = 0;
    float _speed = 0.3f;
    GhostType _ghostType;
};

} // namespace logic

#endif // GHOST_H
