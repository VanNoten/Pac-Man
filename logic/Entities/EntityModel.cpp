#include "EntityModel.h"

namespace logic {

Bounds EntityModel::getBounds() const {
    float halfWidth = _width / 2.0f;
    float halfHeight = _height / 2.0f;

    return {_x - halfWidth, _x + halfWidth, _y - halfHeight, _y + halfHeight};
}

float EntityModel::getX() const { return _x; }

float EntityModel::getY() const { return _y; }

float EntityModel::getWidth() const { return _width; }

float EntityModel::getHeight() const { return _height; }

EntityModel::EntityModel(float x, float y, float width, float height) : _x(x), _y(y), _width(width), _height(height) {}

} // namespace logic