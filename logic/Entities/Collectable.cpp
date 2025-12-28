#include "Collectable.h"

namespace logic {

Collectable::Collectable(float x, float y, float width, float height) : EntityModel(x, y, width, height) {}

bool Collectable::isCollected() const { return _isCollected; }

void Collectable::reset() { _isCollected = false; }

} // namespace logic