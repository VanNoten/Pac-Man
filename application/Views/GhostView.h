#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include <Entities/Ghost.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>
#include <array>

namespace application::views {

/**
 * @brief Renders Ghost entity with animation, changing directions and feared mode.
 *
 * Concrete implementation of EntityView for Ghost entity.
 * Changes sprite based on direction, if ghost is feared and has animation.
 */
class GhostView : public EntityView {
public:
    explicit GhostView(const logic::entities::Ghost& ghost);
    ~GhostView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    /**
     * @brief Calculates all sprite rectangles for each direction, animation frame, and feared mode.
     *
     * Called once in constructor to avoid recalculating sprite positions every frame.
     */
    void initializeSpriteRects();

    /**
     * @brief Updates the sprite's texture rectangle based on current direction, feared mode, and animation frame.
     *
     * Called when direction changes, feared mode changes, or animation frame changes.
     */
    void updateSpriteRect();

    const logic::entities::Ghost& _model;
    sf::Sprite _sprite;
    int _currentFrame = 0;
    float _animationTimer = 0.0f;

    float _x = 0.0f;
    float _y = 0.0f;
    float _width = 0.0f;
    int _directionIndex = 0;
    bool _isFeared = false;

    static constexpr int NUM_DIRECTIONS = 4;
    static constexpr int NUM_FRAMES = 2; // ghosts have 2 frames for the animation
    std::array<std::array<sf::IntRect, NUM_FRAMES>, NUM_DIRECTIONS> _normalSpriteRects;
    std::array<sf::IntRect, NUM_FRAMES> _fearedSpriteRects;

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

} // namespace application::views

#endif // GHOSTVIEW_H
