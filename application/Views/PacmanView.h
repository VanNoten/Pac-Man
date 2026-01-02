#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include "SFML/Graphics/Sprite.hpp"
#include <Entities/Pacman.h>
#include <Views/EntityView.h>
#include <array>

namespace application {

/**
 * @brief Renders Pacman entity with mouth animation and changing directions.
 *
 * Concrete implementation of EntityView for Pacman entity.
 * Changes sprite based on direction and has animation.
 */
class PacmanView : public EntityView {
public:
    explicit PacmanView(const logic::entities::Pacman& pacman);
    ~PacmanView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    /**
     * @brief Calculates all sprite rectangles for each direction and animation frame.
     *
     * Called once in constructor to avoid recalculating sprite positions every frame.
     */
    void initializeSpriteRects();

    /**
     * @brief Updates the sprite's texture rectangle based on current direction and animation frame.
     *
     * Called when direction changes or animation frame changes.
     */
    void updateSpriteRect();

    const logic::entities::Pacman& _model;
    sf::Sprite _sprite;
    int _currentFrame = 0;
    float _animationTimer = 0.0f;

    float _x = 0.0f;
    float _y = 0.0f;
    float _width = 0.0f;
    int _directionIndex = 0;

    static constexpr int NUM_DIRECTIONS = 4;
    static constexpr int NUM_FRAMES = 3; // pacman has 3 frames for the animation
    std::array<std::array<sf::IntRect, NUM_FRAMES>, NUM_DIRECTIONS> _spriteRects;

    // Sprite layout constants
    static constexpr float ANIMATION_SPEED = 0.15f; // amount of seconds a frame lasts before switching
    static constexpr int SPRITE_SIZE = 33;          // size in pixels of pacman
    static constexpr int X_OFFSET = 853;            // x offset pixels on spritesheet for pacman
    static constexpr int Y_OFFSET = 5;              // y offset pixels on spritesheet for pacman
    static constexpr int PIXELS_BETWEEN = 17;       // amount of pixels in between each frame of pacman on spritesheet

    const int _zLevel = 1; // used for rendering order of entities
};

} // namespace application

#endif // PACMANVIEW_H
