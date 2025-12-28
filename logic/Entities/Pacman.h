#ifndef PACMAN_H
#define PACMAN_H
#include "EntityModel.h"
#include "Util/Structs.h"

#include <Util/Constants.h>

namespace logic {

class Pacman : public EntityModel {
public:
    Pacman(float x, float y, float width, float height, int spawnTileX, int spawnTileY);
    void update(float deltaTime) override;

    void move(float x, float y);
    void setPosition(float x, float y);
    [[nodiscard]] float getSpeed() const;

    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;

    void setWantedDirection(Direction direction);
    [[nodiscard]] Direction getWantedDirection() const;

    [[nodiscard]] int getSpawnTileX() const;
    [[nodiscard]] int getSpawnTileY() const;

    void eatGhost() const;

    void die();
    int getLives() const;

private:
    Direction _direction = Direction::RIGHT;
    Direction _wantedDirection = Direction::RIGHT;
    int _spawnTileX = 0;
    int _spawnTileY = 0;
    float _speed = GameConstants::BASE_PACMAN_SPEED;
    int _livesLeft = GameConstants::STARTING_LIVES;
};

} // namespace logic

#endif // PACMAN_H
