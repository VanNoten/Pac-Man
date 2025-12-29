#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include <Entities/Ghost.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>

namespace application {

/**
 * @brief Renders Ghost entity with animation, changing directions and feared mode.
 *
 * Concrete implementation of EntityView for Ghost entity.
 * Changes sprite based on direction, if ghost is feared and has animation.
 */
class GhostView : public EntityView {
public:
    explicit GhostView(const logic::Ghost& ghost);
    ~GhostView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    /**
     * @brief Returns the correct sprite rectangle based on direction, if ghost is feared or not and current
     * animation frame.
     * @return Sprite rectangle that needs to be rendered
     */
    sf::IntRect getSpriteRect() const;

    const logic::Ghost& _model;
    sf::Sprite _sprite;
    int _currentFrame = 0;
    float _animationTimer = 0.0f;

    // Sprite layout constants
    static constexpr float ANIMATION_SPEED = 0.3f; // amount of seconds a frame lasts before switching
    static constexpr int SPRITE_SIZE = 35;         // size in pixels of ghosts
    static constexpr int X_OFFSET = 651;           // x offset pixels on spritesheet for first ghost
    static constexpr int Y_OFFSET = 4;             // y offset pixels on spritesheet for ghosts
    static constexpr int PIXELS_BETWEEN = 15;      // amount of pixels in between each frame of ghosts on spritesheet
    static constexpr int X_OFFSET_FEARED = 1;      // feared ghost only looks in one direction so hardcoded
    static constexpr int Y_OFFSET_FEARED = 554;    // feared ghost only looks in one direction so hardcoded

    const int _zLevel = 1; // used for rendering order of entities
};

} // namespace application

#endif // GHOSTVIEW_H
