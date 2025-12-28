#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateManager.h"
#include "Util/Camera.h"
#include "World/World.h"

#include <SFMLFactory/SFMLFactory.h>
#include <Score/Score.h>

namespace application {

class PlayingState : public State {
public:
    explicit PlayingState(StateManager& stateManager);
    explicit PlayingState(StateManager& stateManager, std::shared_ptr<logic::Score> score, int livesLeft,
                          int currentLevel);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    SFMLFactory _sfmlFactory;
    std::unique_ptr<logic::Camera> _camera;
    std::unique_ptr<logic::World> _world;
    std::shared_ptr<logic::Score> _score;
    int _livesLeft = logic::GameConstants::STARTING_LIVES;
    int _currentLevel = 1;
    bool _mapLoaded = false;
};

} // namespace application

#endif // PLAYINGSTATE_H
