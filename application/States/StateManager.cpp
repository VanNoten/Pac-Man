#include "StateManager.h"

namespace application {

void StateManager::changeState(std::unique_ptr<State>&& state) {
    _states.clear();
    _states.push_back(std::move(state));
}

void StateManager::pushState(std::unique_ptr<State>&& state) { _states.push_back(std::move(state)); }

void StateManager::popState() {
    if (!_states.empty())
        _states.pop_back();
}

void StateManager::handleEvent(const sf::Event& event) const {
    if (!_states.empty())
        _states.back()->handleEvent(event);
}

void StateManager::update() const {
    if (!_states.empty())
        _states.back()->update();
}

void StateManager::render(sf::RenderWindow& window) const {
    for (const std::unique_ptr<State>& state : _states) {
        state->render(window);
    }
}

} // namespace application