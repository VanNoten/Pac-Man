#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateManager.h"
#include "World/World.h"
#include <Camera/Camera.h>
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
    std::vector<std::shared_ptr<EntityView>> _views;
    std::unique_ptr<Camera> _camera;
    std::unique_ptr<logic::World> _world;
    std::shared_ptr<logic::Score> _score;
    int _livesLeft = logic::GameConstants::STARTING_LIVES;
    int _currentLevel = 1;
    bool _mapLoaded = false;
    float _deltaTime = 0.0f;
};

} // namespace application

#endif // PLAYINGSTATE_H
