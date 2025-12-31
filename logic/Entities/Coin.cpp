#include "Coin.h"

namespace logic::entities {

Coin::Coin(float x, float y, float width, float height) : Collectable(x, y, width, height) {}

void Coin::collect() {
    notify(EventType::CoinCollected);
    _isCollected = true;
}

} // namespace logic::entities