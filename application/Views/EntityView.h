#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <Camera/Camera.h>
#include <Observer/Observer.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace application {

class EntityView : public logic::Observer {
public:
    virtual ~EntityView() = default;
    virtual void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) = 0;
    [[nodiscard]] virtual int getZLevel() const = 0;
};

} // namespace application

#endif // ENTITYVIEW_H
