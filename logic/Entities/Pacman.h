#ifndef PACMAN_H
#define PACMAN_H
#include "EntityModel.h"
#include "Util/Structs.h"

#include <Util/Constants.h>

namespace logic::entities {

/**
 * @brief Pacman entity that moves in the world collecting items and avoiding ghosts.
 *
 * Can change direction based on player input (via wanted direction).
 * Has lives that decrement when colliding with a non-feared ghost.
 * Can eat coins, fruits and feared ghosts for points.
 * Respawns at spawn position after death if pacman still has lives left.
 *
 * Movement:
 * - Pacman has a current direction and a wanted direction
 * - util::Direction changes happen at tile centers when the target tile is not a wall
 * - Reverse direction changes are allowed instantly for better responsiveness
 * - Movement is continuous but direction decisions are tile-based (when close enough to tile center)
 */
class Pacman : public EntityModel {
public:
    /**
     * @brief Constructs a new Pacman instance.
     * @param x The X coordinate of pacman.
     * @param y The Y coordinate of pacman.
     * @param width The width of pacman.
     * @param height The height of pacman.
     * @param spawnTileX The tile X coordinate where pacman spawns.
     * @param spawnTileY The tile Y coordinate where pacman spawns.
     */
    Pacman(float x, float y, float width, float height, int spawnTileX, int spawnTileY);

    /**
     * @brief Moves pacman by the given distance.
     * @param x The X distance to move.
     * @param y The Y distance to move.
     */
    void move(float x, float y);

    /**
     * @brief Sets pacman's position to the given coordinates.
     * @param x The new X coordinate.
     * @param y The new Y coordinate.
     */
    void setPosition(float x, float y);

    /**
     * @brief Returns pacman's current speed.
     */
    [[nodiscard]] float getSpeed() const;

    /**
     * @brief Sets pacman's current movement direction.
     * @param direction The direction to set.
     */
    void setDirection(util::Direction direction);

    /**
     * @brief Returns pacman's current movement direction.
     */
    [[nodiscard]] util::Direction getDirection() const;

    /**
     * @brief Sets pacman's wanted movement direction.
     *
     * Pacman will automatically change its current direction to the wanted direction when possible.
     *
     * @param direction The wanted direction to set.
     */
    void setWantedDirection(util::Direction direction);

    /**
     * @brief Returns pacman's wanted movement direction.
     */
    [[nodiscard]] util::Direction getWantedDirection() const;

    /**
     * @brief Returns the tile X coordinate where pacman spawns.
     * @return The spawn tile X coordinate.
     */
    [[nodiscard]] int getSpawnTileX() const;

    /**
     * @brief Returns the tile Y coordinate where pacman spawns.
     * @return The spawn tile Y coordinate.
     */
    [[nodiscard]] int getSpawnTileY() const;

    /**
     * @brief Pacman eats a feared ghost.
     *
     * Sends a GhostEaten event to all attached observers.
     */
    void eatGhost() const;

    /**
     * @brief Pacman dies and lives are decremented by 1.
     */
    void die();

    /**
     * @brief Sets the amount of lives pacman has.
     * @param lives The amount of lives to set.
     */
    void setLives(int lives);

    /**
     * @brief Returns the amount of lives pacman has left.
     */
    [[nodiscard]] int getLives() const;

private:
    util::Direction _direction = util::Direction::RIGHT;
    util::Direction _wantedDirection = util::Direction::RIGHT;
    int _spawnTileX = 0;
    int _spawnTileY = 0;
    float _speed = util::GameConstants::BASE_PACMAN_SPEED;
    int _livesLeft = util::GameConstants::STARTING_LIVES;
};

} // namespace logic::entities

#endif // PACMAN_H
