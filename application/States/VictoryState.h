#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H
#include "State.h"
#include "StateManager.h"

#include <Score/Score.h>
#include <Util/Constants.h>

namespace application {

class VictoryState : public State {
public:
    explicit VictoryState(StateManager& stateManager, std::shared_ptr<logic::Score> score, int livesLeft,
                          int currentLevel);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    std::shared_ptr<logic::Score> _score;
    int _livesLeft = logic::GameConstants::STARTING_LIVES;
    int _currentLevel = 1;
    sf::FloatRect _nextLevelButtonBounds;
    sf::FloatRect _mainMenuButtonBounds;
};

} // namespace application

#endif // VICTORYSTATE_H
