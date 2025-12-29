#include "PacmanView.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace application {

PacmanView::PacmanView(const logic::Pacman& pacman) : _model(pacman) {}

void PacmanView::onNotify(logic::EventType event) {}

void PacmanView::draw(sf::RenderWindow& window, const Camera& camera) {
    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);
    circle.setFillColor(sf::Color::Yellow);
    window.draw(circle);
}

} // namespace application