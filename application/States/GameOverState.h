#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application::states {

/**
 * @brief Game over state showing a button to restart game and a button to return to MenuState
 */
class GameOverState : public State {
public:
    /**
     * @brief Constructs a new GameOverState instance.
     */
    explicit GameOverState(StateManager& stateManager);

    /**
     * @brief Handles player inputs
     *
     * Check for mouse clicks on "Restart Game" and "Main Menu" buttons.
     */
    void handleEvent(const sf::Event& event) override;

    void update() override;

    /**
     * @brief Renders "Game Over" text, "Resume Game" and "Main Menu" buttons
     */
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    sf::FloatRect _restartButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application::states

#endif // GAMEOVERSTATE_H
