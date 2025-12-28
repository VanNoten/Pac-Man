#ifndef GHOST_H
#define GHOST_H
#include "EntityModel.h"

#include <Util/Constants.h>

namespace logic {

enum class GhostType { Locked, AheadChaser, Chaser };

class Ghost : public EntityModel {
public:
    Ghost(float x, float y, float width, float height, int spawnTileX, int spawnTileY, GhostType ghostType);
    void update(float deltaTime) override;
    void move(float x, float y);
    void setPosition(float x, float y);
    void setSpeeds(float chasingSpeed, float fearedSpeed);
    [[nodiscard]] float getSpeed() const;

    [[nodiscard]] GhostType getGhostType() const;

    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;

    void setLastDecisionTile(int tileX, int tileY);
    [[nodiscard]] int getLastDecisionTileX() const;
    [[nodiscard]] int getLastDecisionTileY() const;

    [[nodiscard]] int getSpawnTileX() const;
    [[nodiscard]] int getSpawnTileY() const;

    void setIsFeared(bool status);
    [[nodiscard]] bool getIsFeared() const;

    void setActive(bool status);
    [[nodiscard]] bool getIsActive() const;

private:
    Direction _direction = Direction::RIGHT;
    int _spawnTileX = 0;
    int _spawnTileY = 0;
    int _lastDecisionTileX = 0;
    int _lastDecisionTileY = 0;
    float _speed = GameConstants::BASE_GHOST_SPEED;
    float _fearedSpeed = GameConstants::BASE_FEARED_GHOST_SPEED;
    GhostType _ghostType;
    bool _isFeared = false;
    bool _isActive = false;
};

} // namespace logic

#endif // GHOST_H
