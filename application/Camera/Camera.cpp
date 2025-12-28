#include "Camera.h"

#include <algorithm>

namespace application {

Camera::Camera(const float windowWidth, const float windowHeight)
    : _windowWidth(windowWidth), _windowHeight(windowHeight) {
    _scale = std::min(windowWidth / 2.0f, windowHeight / 2.0f);
    _offsetX = (windowWidth - 2.0f * _scale) / 2.0f;
    _offsetY = (windowHeight - 2.0f * _scale) / 2.0f;
}

void Camera::worldToScreen(const float worldX, const float worldY, float& screenX, float& screenY) const {
    screenX = _offsetX + (worldX + 1.0f) * _scale;
    screenY = _offsetY + (1.0f - worldY) * _scale;
}

float Camera::worldToScreenSize(const float worldSize) const { return worldSize * _scale; }

void Camera::setWindowSize(const float width, const float height) {
    _windowWidth = width;
    _windowHeight = height;
    _scale = std::min(width / 2.0f, height / 2.0f);
    _offsetX = (width - 2.0f * _scale) / 2.0f;
    _offsetY = (height - 2.0f * _scale) / 2.0f;
}

} // namespace application