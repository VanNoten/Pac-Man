#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H
#include "State.h"
#include "StateManager.h"

#include <Score/Score.h>
#include <Util/Constants.h>

namespace application::states {

/**
 * @brief Victory state showing a button to continue to next level and a button to return to MenuState
 */
class VictoryState : public State {
public:
    /**
     * @brief Constructs a new VictoryState instance.
     * Needs some information about the game state to continue to next level.
     */
    explicit VictoryState(StateManager& stateManager, std::shared_ptr<logic::Score> score, int livesLeft,
                          int currentLevel);

    /**
     * @brief Handles player inputs
     *
     * Check for mouse clicks on "Next Level" and "Main Menu" buttons.
     */
    void handleEvent(const sf::Event& event) override;

    void update() override;

    /**
     * @brief Renders "Level Cleared" text, "Next Level" and "Main Menu" buttons
     */
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    std::shared_ptr<logic::Score> _score; // Score that will be forwarded to the new PlayingState
    int _livesLeft =
        logic::util::GameConstants::STARTING_LIVES; // Lives left that will be forwarded to the new PlayingState
    int _currentLevel = 1;                          // Current level that will be forwarded to the new PlayingState
    sf::FloatRect _nextLevelButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application::states

#endif // VICTORYSTATE_H
