#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf {
class Event;
}

namespace application {

class State {
public:
    State() = default;
    virtual ~State() = default;
    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

} // namespace application

#endif // STATE_H
