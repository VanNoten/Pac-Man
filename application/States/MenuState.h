#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"

#include <Score/Score.h>

namespace application::states {

/**
 * @brief Menu state showing title of the game, previous high scores and a play button
 *
 * Previous high scores are limited to the top 5
 * Pressing the play button or pressing enter on the keyboard transitions to PlayingState
 */
class MenuState : public State {
public:
    /**
     * @brief Constructs a new MenuState instance.
     * Initialises Score class to use a method to read the top 5 high scores
     */
    explicit MenuState(StateManager& stateManager);

    /**
     * @brief Handles player inputs
     *
     * Click on the play button or pressing Enter on keyboard both send the player to PlayingState.
     */
    void handleEvent(const sf::Event& event) override;

    void update() override;

    /**
     * @brief Renders title, high scores and play button
     */
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    std::shared_ptr<logic::Score> _score;
    std::vector<int> _highScores = {};
    sf::FloatRect _playButtonBounds; // Bounds for the play button to check if player clicked on it
};

} // namespace application::states

#endif // MENUSTATE_H
