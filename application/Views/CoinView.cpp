#include "CoinView.h"

#include <Resources/ResourceLoader.h>
#include <SFML/Graphics/CircleShape.hpp>

namespace application {

using namespace logic::entities;

CoinView::CoinView(const Coin& coin)
    : _model(coin), _x(coin.getX()), _y(coin.getY()), _width(coin.getWidth()), _isCollected(coin.isCollected()) {
    const sf::Texture& texture = ResourceLoader::getInstance().getSpriteSheet();
    _sprite.setTexture(texture);
    _sprite.setTextureRect(_spriteRect);
}

void CoinView::onNotify(const logic::EventType event) {
    if (event == logic::EventType::CoinCollected) {
        _isCollected = true;
    }
}

void CoinView::draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) {
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

int CoinView::getZLevel() const { return _zLevel; }

} // namespace application