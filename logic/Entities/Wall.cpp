#include "Wall.h"

namespace logic {

Wall::Wall(const float x, const float y, const float width, const float height)
    : EntityModel(x, y), _width(width), _height(height) {}

float Wall::getWidth() const { return _width; }

float Wall::getHeight() const { return _height; }

} // namespace logic