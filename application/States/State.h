#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf {
class Event;
}

namespace application {

/**
 * @brief Abstract base class for states
 *
 * Implements the State design pattern.
 * A state is a specific mode of the game for example main menu, gameplay, paused, game over/victory.
 */
class State {
public:
    State() = default;
    virtual ~State() = default;

    /**
     * @brief Handles event forwarded by StateManager
     */
    virtual void handleEvent(const sf::Event& event) = 0;

    /**
     * @brief Updates state
     */
    virtual void update() = 0;

    /**
     * @brief Renders state to window
     */
    virtual void render(sf::RenderWindow& window) = 0;
};

} // namespace application

#endif // STATE_H
