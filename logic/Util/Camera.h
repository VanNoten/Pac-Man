#ifndef CAMERA_H
#define CAMERA_H

namespace logic {

class Camera {
public:
    Camera(float windowWidth, float windowHeight);
    void worldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;
    [[nodiscard]] float worldToScreenSize(float worldSize) const;
    void setWindowSize(float width, float height);

private:
    float _windowWidth;
    float _windowHeight;
    float _scale;
    float _offsetX;
    float _offsetY;
};

} // namespace logic

#endif // CAMERA_H
