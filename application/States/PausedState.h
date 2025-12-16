#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H
#include "State.h"
#include "StateManager.h"

namespace application {

class PausedState : public State {
public:
    explicit PausedState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
};

} // namespace application

#endif // PAUSEDSTATE_H
