#ifndef WORLD_H
#define WORLD_H
#include "Entities/Coin.h"
#include "Entities/Wall.h"

#include <AbstractFactory/AbstractFactory.h>
#include <Entities/Pacman.h>
#include <Observer/Subject.h>
#include <memory>
#include <string>
#include <vector>

namespace logic {

/**
 * @brief Enumeration of player input actions for controlling Pacman.
 */
enum class Actions { Up, Down, Left, Right };

/**
 * @brief Main game controller that manages all entities and game logic.
 *
 * The World class is responsible for:
 * - Managing all game entities (pacman, ghosts, coins, fruits, walls).
 * - Handling received actions from PlayingState.
 * - Updating entity positions and states each frame.
 * - Detecting collisions between entities.
 * - Managing game state (level progression, lives, victory/defeat conditions).
 * - Implementing ghost AI behavior (chasing, feared, activation delays).
 *
 * The coordinate system is bounded by [-1, 1] in both dimensions.
 * Entity direction changes and wall collision detection is tile-based but the actual entity movement remains
 * continuous. Collision detection between entities other than walls is done using AABB collision.
 *
 * Implements the Observer/Subject design pattern.
 */
class World : public Subject {
public:
    /**
     * @brief Constructs a new World instance.
     * @param factory Reference to an AbstractFactory used to create game entities.
     */
    World(AbstractFactory& factory);
    ~World() = default;

    /**
     * @brief Handles a player input action and updates pacman's direction.
     * @param action The action to process (Up, Down, Left, or Right).
     */
    void handleAction(Actions action) const;

    /**
     * @brief Updates the game world state for one frame.
     *
     * - Updates Pacman and ghost positions
     * - Activates ghosts based on their delay timers
     * - Manages the feared state timer for ghosts
     * - Detects and handles collisions (Pacman-ghost, Pacman-coin, Pacman-fruit, wall collision)
     * - Triggers game state changes (victory, game over)
     *
     * @param deltaTime Time elapsed since the last update, in seconds.
     */
    void update(float deltaTime);

    /**
     * @brief Loads a map from a vector of strings where each character represents the entity to initialise.
     *
     * - '#' = Wall
     * - '@' = Pacman
     * - '.' = Coin
     * - 'F' = Fruit
     * - '1' = Ghost 1 (Locked type)
     * - '2' = Ghost 2 (AheadChaser1 type)
     * - '3' = Ghost 3 (AheadChaser2 type)
     * - '4' = Ghost 4 (Chaser type)
     * - Any other character = Empty tile
     *
     * @param map Vector of strings representing the map layout.
     * @param pacmanLives Initial number of lives for Pacman. Defaults to GameConstants::STARTING_LIVES.
     * @param currentLevel The level number being loaded. Defaults to 1.
     */
    void loadMap(const std::vector<std::string>& map, int pacmanLives = util::GameConstants::STARTING_LIVES,
                 int currentLevel = 1);

    /**
     * @brief Gets the current level number.
     */
    [[nodiscard]] int getCurrentLevel() const;

    /**
     * @brief Returns the flag that determines if the game is over.
     */
    [[nodiscard]] bool getIsGameOver() const;

    /**
     * @brief Returns the flag that determines if the level has been cleared.
     */
    [[nodiscard]] bool getIsGameVictory() const;

    /**
     * @brief Returns the amount of lives pacman has left.
     */
    [[nodiscard]] int getPacmanLives() const;

private:
    /**
     * @brief Updates pacman's position based on current direction and handles direction changes.
     *
     * Pacman can change direction when close to a tile center, but only if the
     * target tile is not a wall. Reverse direction changes are allowed instantly for responsiveness.
     *
     * @param deltaTime Time since the last update
     */
    void handlePacmanMovement(float deltaTime) const;

    /**
     * @brief Updates a ghost's position and determines its next direction using AI behavior logic.
     *
     * Ghosts make direction decisions when they reach tile centers. The decision
     * depends on the ghost's type and whether its in a feared state.
     *
     * @param ghost Reference to the ghost to handle
     * @param deltaTime Time since the last update
     */
    void handleGhostMovement(entities::Ghost& ghost, float deltaTime) const;

    /**
     * @brief Activates ghosts based on their individual delay timers.
     *
     * Each ghost has a delay timer that determines when it becomes active.
     * This method decrements timers and activates ghosts when their timer reaches zero.
     *
     * @param deltaTime Time since the last update
     */
    void activateGhosts(float deltaTime);

    /**
     * @brief Sets all ghosts to feared mode and reverses their direction if possible.
     *
     * Called when Pacman collects a fruit. The feared duration decreases with level.
     */
    void fearGhosts();

    /**
     * @brief Handles pacman's death, decrements lives, and resets entities or ends the game.
     *
     * If pacman has lives remaining, entities are reset to their spawn positions.
     * Else, a GameOver event is sent to observers.
     */
    void handlePacmanDeath();

    /**
     * @brief Sets ghost speeds based on the current level.
     *
     * Ghost speeds increase with level but is capped at a maximum MAX_GHOST_SPEED and MAX_FEARED_GHOST_SPEED
     */
    void setSpeedsForLevel();

    /**
     * @brief Resets pacman and all ghosts to their spawn positions and initial states.
     *
     * Called after pacman dies but still has lives remaining.
     */
    void resetGhostsAndPacman();

    /**
     * @brief Checks if two bounding boxes are colliding using AABB collision detection.
     * @param A First bounding box.
     * @param B Second bounding box.
     * @return True if the bounding boxes overlap, false otherwise.
     */
    [[nodiscard]] static bool isColliding(const util::Bounds& A, const util::Bounds& B);

    /**
     * @brief Converts a tile X coordinate to the world X coordinate of the tile center.
     * @param tileX The tile X coordinate.
     * @return The world X coordinate of the tile center.
     */
    [[nodiscard]] float getTileCenterX(int tileX) const;

    /**
     * @brief Converts a tile Y coordinate to the world Y coordinate of the tile center.
     * @param tileY The tile Y coordinate.
     * @return The world Y coordinate of the tile center.
     */
    [[nodiscard]] float getTileCenterY(int tileY) const;

    /**
     * @brief Converts a world X coordinate to the corresponding tile X coordinate.
     * @param x The world X coordinate.
     * @return The tile X coordinate.
     */
    [[nodiscard]] int getTileX(float x) const;

    /**
     * @brief Converts a world Y coordinate to the corresponding tile Y coordinate.
     * @param y The world Y coordinate.
     * @return The tile Y coordinate.
     */
    [[nodiscard]] int getTileY(float y) const;

    /**
     * @brief Gets the tile coordinates in the given direction from a starting tile.
     * @param tileX Starting tile X coordinate.
     * @param tileY Starting tile Y coordinate.
     * @param direction util::Direction to move in.
     * @return Pair of (tileX, tileY) coordinates in the given direction.
     */
    [[nodiscard]] static std::pair<int, int> getTileInDirection(int tileX, int tileY, util::Direction direction);

    /**
     * @brief Checks if given tile is a wall.
     *
     * Out of map coordinates are considered as walls.
     *
     * @param tileX The tile X coordinate.
     * @param tileY The tile Y coordinate.
     * @return True if given tile is a wall or coordinates are out of map, false otherwise.
     */
    [[nodiscard]] bool isWallAtTile(int tileX, int tileY) const;

    /**
     * @brief Calculates the Manhattan distance between two tiles.
     * @param fromTileX Starting tile X coordinate.
     * @param fromTileY Starting tile Y coordinate.
     * @param toTileX Destination tile X coordinate.
     * @param toTileY Destination tile Y coordinate.
     * @return The Manhattan distance.
     */
    [[nodiscard]] static int getManhattanDistance(int fromTileX, int fromTileY, int toTileX, int toTileY);

    /**
     * @brief Returns the opposite direction of the given direction.
     */
    [[nodiscard]] static util::Direction getReverseDirection(util::Direction direction);

    /**
     * @brief Returns the possible directions a ghost can switch to.
     *
     * It does not include the opposite direction unless its the only possibility.
     *
     * @param ghost Reference to ghost
     */
    [[nodiscard]] std::vector<util::Direction> getPossibleDirections(const entities::Ghost& ghost) const;

    /**
     * @brief Determines the next direction for a ghost based on its ghost type.
     *
     * Ghost AI behavior:
     * - Locked: 50% chance to change direction at intersection, otherwise continues current direction
     * - AheadChaser1/AheadChaser2: Minimizes manhattan distance to the tile ahead of pacman
     * - Chaser: Minimizes manhattan distance to pacman's current tile
     *
     * @param ghost Reference to the ghost.
     * @return The direction the ghost should move next.
     */
    [[nodiscard]] util::Direction getNextGhostDirection(const entities::Ghost& ghost) const;

    /**
     * @brief Determines the next direction for a feared ghost.
     *
     * Feared ghosts maximize manhattan distance from pacman's current tile.
     *
     * @param ghost Reference to the feared ghost.
     * @return The direction the ghost should move next.
     */
    [[nodiscard]] util::Direction getNextFearedGhostDirection(const entities::Ghost& ghost) const;

    std::vector<std::string> _map = {};  // Vector of strings representing map layout
    float _originX, _originY, _cell = 0; // Coordinate system variables
    AbstractFactory& _factory;           // Factory for creating entities

    std::vector<std::unique_ptr<entities::Wall>> _walls;   // All wall entities
    std::vector<std::unique_ptr<entities::Coin>> _coins;   // All coin entities
    std::vector<std::unique_ptr<entities::Fruit>> _fruits; // All fruit entities
    std::vector<std::unique_ptr<entities::Ghost>> _ghosts; // All ghost entities
    std::unique_ptr<entities::Pacman> _pacman;             // Pacman entity

    float _fearedTimer = 0.0f; // Remaining time for feared mode
    bool _ghostsAreFeared = false;

    std::vector<float> _ghostDelayTimers = {}; // Individual activation delay timers for each ghost
    bool _allGhostsActive = false;

    bool _isGameOver = false;
    bool _isGameVictory = false;

    int _collectablesLeft = 0; // Number of coins and fruits left

    int _currentLevel = 1;
};

} // namespace logic

#endif // WORLD_H
