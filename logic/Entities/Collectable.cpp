#include "Collectable.h"

namespace logic {

Collectable::Collectable(const float x, const float y, const float width, const float height)
    : EntityModel(x, y, width, height) {}

bool Collectable::isCollected() const { return _isCollected; }

} // namespace logic