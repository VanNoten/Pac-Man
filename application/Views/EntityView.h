#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <Camera/Camera.h>
#include <Observer/Observer.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace application::views {

/**
 * @brief Abstract base class for rendering the entity models using SFML.
 *
 * This is the View component in MVC design pattern, responsible for the visual representation of entities.
 */
class EntityView : public logic::Observer {
public:
    virtual ~EntityView() = default;

    /**
     * @brief Renders the entity to the SFML window.
     *
     * @param window SFML window to render to.
     * @param camera Camera to convert world coordinates to pixel coordinates.
     * @param deltaTime Time since last frame used for animations.
     */
    virtual void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) = 0;

    /**
     * @brief Returns z-level of entity
     *
     * The z-level of an EntityView determines which entities are rendered over others.
     * For example ghosts and pacman have higher z-level than walls, coins and fruits so they will get rendered on top
     * of them.
     */
    [[nodiscard]] virtual int getZLevel() const = 0;
};

} // namespace application::views

#endif // ENTITYVIEW_H
