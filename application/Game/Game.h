#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

namespace application {

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window_;
};

} // namespace application

#endif // GAME_H
