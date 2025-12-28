#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"

#include <Score/Score.h>

namespace application {

class MenuState : public State {
public:
    explicit MenuState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    std::shared_ptr<logic::Score> _score;
    sf::FloatRect _playButtonBounds;
};

} // namespace application

#endif // MENUSTATE_H
