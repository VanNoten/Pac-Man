#ifndef CAMERA_H
#define CAMERA_H

namespace application {

class Camera {
public:
    Camera(float windowWidth, float windowHeight);
    void worldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;
    [[nodiscard]] float worldToScreenSize(float worldSize) const;

private:
    float _windowWidth;
    float _windowHeight;
    float _scale;
    float _offsetX;
    float _offsetY;
};

} // namespace application

#endif // CAMERA_H
