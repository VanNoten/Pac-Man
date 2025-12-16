#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"

namespace application {

class MenuState : public State {
public:
    explicit MenuState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
};

} // namespace application

#endif // MENUSTATE_H
