#include "CoinView.h"

#include <SFML/Graphics/CircleShape.hpp>

namespace application {

CoinView::CoinView(const logic::Coin& coin) : _model(coin) {}

void CoinView::onNotify(logic::EventType event) {}

void CoinView::draw(sf::RenderWindow& window, const Camera& camera) {
    if (_model.isCollected())
        return;

    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    sf::CircleShape circle(radius);
    circle.setPosition(screenX - radius, screenY - radius);
    circle.setFillColor(sf::Color::White);
    window.draw(circle);
}

} // namespace application