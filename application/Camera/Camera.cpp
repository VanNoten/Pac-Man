#include "Camera.h"

#include <algorithm>

namespace application {

Camera::Camera(const float windowWidth, const float windowHeight)
    : _windowWidth(windowWidth), _windowHeight(windowHeight) {
    // World is bounded by [-1, 1] in both dimensions which means 2x2 units.
    // The scale represents amount of pixels per unit.
    // We take std::min so we can be sure the square world fits on the screen without stretching.
    _scale = std::min(windowWidth / 2.0f, windowHeight / 2.0f);

    // Padding needed to center world view on screen
    _offsetX = (windowWidth - 2.0f * _scale) / 2.0f;
    _offsetY = (windowHeight - 2.0f * _scale) / 2.0f;
}

void Camera::worldToScreen(const float worldX, const float worldY, float& screenX, float& screenY) const {
    screenX = _offsetX + (worldX + 1.0f) * _scale;
    screenY = _offsetY + (1.0f - worldY) * _scale;
}

float Camera::worldToScreenSize(const float worldSize) const { return worldSize * _scale; }

void Camera::resize(const float windowWidth, const float windowHeight) {
    _windowWidth = windowWidth;
    _windowHeight = windowHeight;

    _scale = std::min(windowWidth / 2.0f, windowHeight / 2.0f);
    _offsetX = (windowWidth - 2.0f * _scale) / 2.0f;
    _offsetY = (windowHeight - 2.0f * _scale) / 2.0f;
}

} // namespace application