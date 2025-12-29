#include "GhostView.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace application {

GhostView::GhostView(const logic::Ghost& ghost) : _model(ghost) { _ghostType = ghost.getGhostType(); }

void GhostView::onNotify(logic::EventType event) {}

void GhostView::draw(sf::RenderWindow& window, const Camera& camera) {
    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);

    if (!_model.getIsFeared()) {
        switch (_ghostType) {
        case logic::GhostType::Locked:
            circle.setFillColor(sf::Color::Red);
            break;
        case logic::GhostType::AheadChaser:
            circle.setFillColor(sf::Color::Magenta);
            break;
        case logic::GhostType::Chaser:
            circle.setFillColor(sf::Color::Yellow);
            break;
        default:
            break;
        }
    } else {
        circle.setFillColor(sf::Color::Green);
    }

    window.draw(circle);
}

} // namespace application