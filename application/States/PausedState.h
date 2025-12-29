#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application {

/**
 * @brief Paused state showing a button to continue playing and a button to return to MenuState
 */
class PausedState : public State {
public:
    explicit PausedState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    sf::FloatRect _resumeButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application

#endif // PAUSEDSTATE_H
