#ifndef GHOST_H
#define GHOST_H
#include "EntityModel.h"

#include <Util/Constants.h>

namespace logic::entities {

/**
 * @brief Enumeration of ghost AI behavior types.
 *
 * Locked: 50% chance to change direction at intersections
 * AheadChaser1/AheadChaser2: Chase the tile ahead of pacman's current position
 * Chaser: Directly chase pacman's current tile position
 */
enum class GhostType { Locked, AheadChaser1, AheadChaser2, Chaser };

/**
 * @brief Ghost entity that chases or runs from pacman based on its state and type.
 *
 * Ghost movement is determined by GhostType, if the ghost is feared and the position relative to pacman.
 *
 * Ghosts start inactive and are activated after a delay timer.
 * When feared ghosts run from pacman and move slower. If not feared ghosts chase pacman and move at normal speed.
 * Ghosts can be eaten by pacman when feared, when a ghost is eaten they teleport back to their spawn tile.
 */
class Ghost : public EntityModel {
public:
    /**
     * @brief Constructs a new Ghost instance.
     * @param x The X coordinate of the ghost.
     * @param y The Y coordinate of the ghost.
     * @param width The width of the ghost.
     * @param height The height of the ghost.
     * @param spawnTileX The tile X coordinate where the ghost spawns.
     * @param spawnTileY The tile Y coordinate where the ghost spawns.
     * @param ghostType The AI behavior type of the ghost.
     */
    Ghost(float x, float y, float width, float height, int spawnTileX, int spawnTileY, GhostType ghostType);

    /**
     * @brief Moves the ghost by the given distance.
     * @param x The X distance to move.
     * @param y The Y distance to move.
     */
    void move(float x, float y);

    /**
     * @brief Sets the ghost's position to the given coordinates.
     * @param x The new X coordinate.
     * @param y The new Y coordinate.
     */
    void setPosition(float x, float y);

    /**
     * @brief Sets the ghost's chasing and feared speeds.
     * @param chasingSpeed The speed when chasing pacman.
     * @param fearedSpeed The speed when running from pacman.
     */
    void setSpeeds(float chasingSpeed, float fearedSpeed);

    /**
     * @brief Returns the ghost's current speed.
     * @return Returns the feared speed if the ghost is feared, otherwise returns the chasing speed.
     */
    [[nodiscard]] float getSpeed() const;

    /**
     * @brief Returns the ghost's AI behavior type.
     */
    [[nodiscard]] GhostType getGhostType() const;

    /**
     * @brief Sets the ghost's current movement direction.
     * @param direction The direction to set.
     */
    void setDirection(util::Direction direction);

    /**
     * @brief Returns the ghost's current movement direction.
     */
    [[nodiscard]] util::Direction getDirection() const;

    /**
     * @brief Sets the tile coordinates where the ghost last made a direction decision.
     *
     * Used to prevent the ghost from making multiple direction decisions at the same tile.
     *
     * @param tileX The tile X coordinate.
     * @param tileY The tile Y coordinate.
     */
    void setLastDecisionTile(int tileX, int tileY);

    /**
     * @brief Returns the X coordinate of the tile where the ghost last made a direction decision.
     * @return The tile X coordinate.
     */
    [[nodiscard]] int getLastDecisionTileX() const;

    /**
     * @brief Returns the Y coordinate of the tile where the ghost last made a direction decision.
     * @return The tile Y coordinate.
     */
    [[nodiscard]] int getLastDecisionTileY() const;

    /**
     * @brief Returns the tile X coordinate where the ghost spawns.
     * @return The spawn tile X coordinate.
     */
    [[nodiscard]] int getSpawnTileX() const;

    /**
     * @brief Returns the tile Y coordinate where the ghost spawns.
     * @return The spawn tile Y coordinate.
     */
    [[nodiscard]] int getSpawnTileY() const;

    /**
     * @brief Sets whether the ghost is in feared mode.
     * @param status True to set the ghost as feared, false otherwise.
     */
    void setIsFeared(bool status);

    /**
     * @brief Returns whether the ghost is in feared mode.
     * @return True if feared, false otherwise.
     */
    [[nodiscard]] bool getIsFeared() const;

    /**
     * @brief Sets whether the ghost is active.
     * @param status True to activate the ghost, false to deactivate.
     */
    void setActive(bool status);

    /**
     * @brief Returns whether the ghost is active.
     * @return True if active, false otherwise.
     */
    [[nodiscard]] bool getIsActive() const;

private:
    util::Direction _direction = util::Direction::RIGHT;
    int _spawnTileX = 0;
    int _spawnTileY = 0;
    int _lastDecisionTileX = 0;
    int _lastDecisionTileY = 0;
    float _speed = util::GameConstants::BASE_GHOST_SPEED;
    float _fearedSpeed = util::GameConstants::BASE_FEARED_GHOST_SPEED;
    GhostType _ghostType;
    bool _isFeared = false;
    bool _isActive = false;
};

} // namespace logic::entities

#endif // GHOST_H
