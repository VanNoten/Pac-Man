#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <States/StateManager.h>

namespace application {

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow _window;
    StateManager _stateManager;
};

} // namespace application

#endif // GAME_H
