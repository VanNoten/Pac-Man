#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#include <memory>
#include <vector>

namespace sf {
class Event;
class RenderWindow;
}

namespace application {

class StateManager {
public:
    StateManager() = default;
    ~StateManager() = default;

    void changeState(std::unique_ptr<State>&& state);
    void pushState(std::unique_ptr<State>&& state);
    void popState();

    void handleEvent(const sf::Event& event) const;
    void update() const;
    void render(sf::RenderWindow& window) const;

private:
    std::vector<std::unique_ptr<State>> _states;
};

} // namespace application

#endif // STATEMANAGER_H
