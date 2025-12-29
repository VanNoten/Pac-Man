#include "WallView.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace application {

WallView::WallView(const logic::Wall& wall) : _model(wall) {}

void WallView::onNotify(logic::EventType event) {}

void WallView::draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) {
    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    float width = camera.worldToScreenSize(_model.getWidth());
    float height = camera.worldToScreenSize(_model.getHeight());

    sf::RectangleShape rect({width, height});
    rect.setPosition(screenX - width * 0.5f, screenY - height * 0.5f);
    rect.setFillColor(sf::Color(0, 0, 255));
    window.draw(rect);
}

int WallView::getZLevel() const { return _zLevel; }

} // namespace application