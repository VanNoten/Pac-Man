#include "StateManager.h"

namespace application::states {

void StateManager::changeState(std::unique_ptr<State>&& state) {
    while (!_states.empty()) {
        _states.pop();
    }
    _states.push(std::move(state));
}

void StateManager::pushState(std::unique_ptr<State>&& state) { _states.push(std::move(state)); }

void StateManager::popState() {
    if (!_states.empty())
        _states.pop();
}

void StateManager::handleEvent(const sf::Event& event) const {
    if (!_states.empty())
        _states.top()->handleEvent(event);
}

void StateManager::update() const {
    if (!_states.empty())
        _states.top()->update();
}

void StateManager::render(sf::RenderWindow& window) const {
    if (!_states.empty())
        _states.top()->render(window);
}

} // namespace application::states