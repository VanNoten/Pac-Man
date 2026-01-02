#include "FruitView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application::views {

using namespace logic::entities;

FruitView::FruitView(const Fruit& fruit)
    : _model(fruit), _x(fruit.getX()), _y(fruit.getY()), _width(fruit.getWidth()), _isCollected(fruit.isCollected()) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
    _sprite.setTextureRect(_spriteRect);
}

void FruitView::onNotify(const logic::EventType event) {
    if (event == logic::EventType::FruitCollected) {
        _isCollected = true;
    }
}

void FruitView::draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) {
    if (_isCollected)
        return;

    float screenX;
    float screenY;
    camera.worldToScreen(_x, _y, screenX, screenY);
    const float radius = camera.worldToScreenSize(_width * 0.5f);

    const float scale = (radius * 2.0f) / SPRITE_SIZE;
    _sprite.setScale(scale, scale);
    _sprite.setPosition(screenX - radius, screenY - radius);

    window.draw(_sprite);
}

int FruitView::getZLevel() const { return _zLevel; }

} // namespace application::views