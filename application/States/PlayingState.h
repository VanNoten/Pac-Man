#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateManager.h"
#include "World/World.h"
#include <Camera/Camera.h>
#include <SFMLFactory/SFMLFactory.h>
#include <Score/Score.h>

namespace application {

/**
 * @brief Playing state representing gameplay where the player controls Pac-Man.
 *
 * PlayingState handles:
 *  - Creating Score class to track the score
 *  - Creating World class and passing SFML Factory (Concrete Factory to create entities)
 *  - Translating keyboard input to world actions for movement
 *  - Calling update method on world and score each frame
 *  - Checking if a state transition is needed
 *  - Rendering all entity views, score, lives left and current level
 */
class PlayingState : public State {
public:
    /**
     * @brief Constructor for starting a new game
     */
    explicit PlayingState(StateManager& stateManager);

    /**
     * @brief Constructor for continuing to the next level
     */
    explicit PlayingState(StateManager& stateManager, std::shared_ptr<logic::Score> score, int livesLeft,
                          int currentLevel);

    /**
     * @brief Handles player inputs that move pacman
     */
    void handleEvent(const sf::Event& event) override;

    /**
     * @brief Handles calling methods from world and score.
     *
     * If map hasn't been loaded yet call loadMap on world, attach the score observer to the world, get the views
     * from the SFML factory and sort them by descending Z-level to ensure pacman and ghosts are drawn over other
     * entities.
     *
     * When the map is loaded get deltaTime and pass it to world and score update methods. Then check the world state to
     * determine if a state transition to GameOverState or VictoryState is needed.
     */
    void update() override;

    /**
     * @brief Renders all entity views, score, lives left and current level.
     */
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    SFMLFactory
        _sfmlFactory; // Concrete factory that the world class uses to create entities and attach observers and views
    std::vector<std::shared_ptr<EntityView>> _views = {}; // All entity views
    std::unique_ptr<Camera> _camera;      // Camera class to convert world coordinates to pixel coordinates
    std::unique_ptr<logic::World> _world; // Game logic controller that owns and manages all entities
    std::shared_ptr<logic::Score> _score; // Score class to track the score, forwarded to next PlayingState
    int _livesLeft = logic::util::GameConstants::STARTING_LIVES; // Lives left, forwarded to next PlayingState
    int _currentLevel = 1;                                       // Current level, forwarded to next PlayingState
    bool _mapLoaded = false;                                     // Flag to load map if it hasn't been loaded yet
    float _deltaTime = 0.0f; // deltaTime is set in update() each frame, render() will use this value
};

} // namespace application

#endif // PLAYINGSTATE_H
