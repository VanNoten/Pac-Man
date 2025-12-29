#include "FruitView.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace application {

FruitView::FruitView(const logic::Fruit& fruit) : _model(fruit) {}

void FruitView::onNotify(logic::EventType event) {}

void FruitView::draw(sf::RenderWindow& window, const Camera& camera) {
    if (_model.isCollected())
        return;

    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);
}

} // namespace application