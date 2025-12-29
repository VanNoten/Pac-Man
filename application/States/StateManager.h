#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#include <memory>
#include <stack>

namespace sf {
class Event;
class RenderWindow;
} // namespace sf

namespace application {

/**
 * @brief Manages game states using a state stack.
 *
 * State transitions are determined by the states themselves not the StateManager.
 * Pushed state will be a new object and not an already initialised state.
 *
 * The current state is the state at the top of the stack.
 */
class StateManager {
public:
    StateManager() = default;
    ~StateManager() = default;

    /**
     * @brief Clears stack and pushes a new state (will become the current state).
     * @param state The new state to push onto the stack.
     */
    void changeState(std::unique_ptr<State>&& state);

    /**
     * @brief Pushes a new state (will become the current state).
     * @param state The new state to push onto the stack.
     */
    void pushState(std::unique_ptr<State>&& state);

    /**
     * @brief Pops the current state.
     */
    void popState();

    /**
     * @brief Forwards event to the current state.
     */
    void handleEvent(const sf::Event& event) const;

    /**
     * @brief Updates the current state.
     */
    void update() const;

    /**
     * @brief Renders the current state.
     */
    void render(sf::RenderWindow& window) const;

private:
    /// State stack
    std::stack<std::unique_ptr<State>> _states;
};

} // namespace application

#endif // STATEMANAGER_H
