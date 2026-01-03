#ifndef CAMERA_H
#define CAMERA_H

namespace application {

/**
 * @brief Converts world coordinates to screen coordinates.
 *
 * The world coordinate system is bounded by [-1, 1] in both dimensions.
 * The camera calculates a scale based on the window dimensions to maintain aspect ratio
 * and centers the world view on the screen using offsets.
 */
class Camera {
public:
    /**
     * @brief Constructs a new Camera instance.
     * @param windowWidth Width of the window in pixels.
     * @param windowHeight Height of the window in pixels.
     */
    Camera(float windowWidth, float windowHeight);

    /**
     * @brief Converts world coordinates to screen coordinates.
     * @param worldX World X coordinate.
     * @param worldY World Y coordinate.
     * @param[out] screenX Output for the screen X coordinate in pixels.
     * @param[out] screenY Output for the screen Y coordinate in pixels.
     */
    void worldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;

    /**
     * @brief Converts a world size to screen size.
     * @param worldSize Size in world.
     * @return Size in pixels.
     */
    [[nodiscard]] float worldToScreenSize(float worldSize) const;

    /**
     * @brief Updates the camera parameters for the resized window.
     * @param windowWidth New width of the window in pixels.
     * @param windowHeight New height of the window in pixels.
     */
    void resize(float windowWidth, float windowHeight);

private:
    float _windowWidth = 0;
    float _windowHeight = 0;
    float _scale = 0;
    float _offsetX = 0;
    float _offsetY = 0;
};

} // namespace application

#endif // CAMERA_H
