#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application {

/**
 * @brief Game over state showing a button to restart game and a button to return to MenuState
 */
class GameOverState : public State {
public:
    explicit GameOverState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    sf::FloatRect _restartButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application

#endif // GAMEOVERSTATE_H
