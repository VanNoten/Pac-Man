#include "FruitView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application {

using namespace logic::entities;

FruitView::FruitView(const Fruit& fruit) : _model(fruit) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
    _sprite.setTextureRect(_spriteRect);
}

void FruitView::onNotify(logic::EventType event) {}

void FruitView::draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) {
    if (_model.isCollected())
        return;

    float screenX;
    float screenY;
    camera.worldToScreen(_model.getX(), _model.getY(), screenX, screenY);
    const float radius = camera.worldToScreenSize(_model.getWidth() * 0.5f);

    const float scale = (radius * 2.0f) / SPRITE_SIZE;
    _sprite.setScale(scale, scale);
    _sprite.setPosition(screenX - radius, screenY - radius);

    window.draw(_sprite);
}

int FruitView::getZLevel() const { return _zLevel; }

} // namespace application