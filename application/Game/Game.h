#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <States/StateManager.h>

namespace application {

/**
 * @brief Application entry point.
 *
 * Owns the SFML window and runs the main loop.
 */
class Game {
public:
    /**
     * @brief Constructs application window and sets initial state.
     *
     * Initialises StateManager with MenuState.
     */
    Game();

    /**
     * @brief Runs the main game loop.
     *
     * Polls SFML events and forwards them to StateManager, then updates and renders the current state each frame.
     */
    void run();

private:
    sf::RenderWindow _window;
    StateManager _stateManager;
};

} // namespace application

#endif // GAME_H
