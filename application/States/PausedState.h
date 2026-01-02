#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application::states {

/**
 * @brief Paused state showing a button to continue playing and a button to return to MenuState
 */
class PausedState : public State {
public:
    /**
     * @brief Constructs a new PausedState instance.
     */
    explicit PausedState(StateManager& stateManager);

    /**
     * @brief Handles player inputs
     *
     * Check for mouse clicks on "Resume Game" and "Main Menu" buttons.
     */
    void handleEvent(const sf::Event& event) override;

    void update() override;

    /**
     * @brief Renders the "Resume Game" and "Main Menu" buttons
     */
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    sf::FloatRect _resumeButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application::states

#endif // PAUSEDSTATE_H
