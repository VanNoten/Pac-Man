#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application {

class VictoryState : public State {
public:
    explicit VictoryState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    sf::FloatRect _nextLevelButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application

#endif // VICTORYSTATE_H
