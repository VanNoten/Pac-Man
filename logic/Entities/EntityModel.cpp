#include "EntityModel.h"

namespace logic {

float EntityModel::getX() const { return _x; }

float EntityModel::getY() const { return _y; }

EntityModel::EntityModel(const float x, const float y) : _x(x), _y(y) {}

} // namespace logic