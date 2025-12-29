#include "CoinView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application {

CoinView::CoinView(const logic::Coin& coin) : _model(coin) {
    const sf::Texture& texture = ResourceLoader::getInstance()->getSpriteSheet();
    _sprite.setTexture(texture);
    _sprite.setTextureRect(_spriteRect);
}

void CoinView::onNotify(logic::EventType event) {}

void CoinView::draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) {
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

} // namespace application