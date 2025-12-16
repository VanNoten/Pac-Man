#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateManager.h"
#include "Util/Camera.h"
#include "World/World.h"

namespace application {

class PlayingState : public State {
public:
    explicit PlayingState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    StateManager& _stateManager;
    std::unique_ptr<logic::Camera> _camera;
    std::unique_ptr<logic::World> _world;
    bool _mapLoaded = false;
};

} // namespace application

#endif // PLAYINGSTATE_H
