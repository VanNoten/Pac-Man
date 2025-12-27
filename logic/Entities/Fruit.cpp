#include "Fruit.h"

namespace logic {

Fruit::Fruit(float x, float y, float width, float height) : Collectable(x, y, width, height) {}

void Fruit::collect() {
    notify(EventType::FruitCollected);
    _isCollected = true;
}

} // namespace logic