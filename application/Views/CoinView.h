#ifndef COINVIEW_H
#define COINVIEW_H

#include <Entities/Coin.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>

namespace application {

/**
 * @brief Renders Coin entities
 *
 * Concrete implementation of EntityView for Coin entity
 */
class CoinView : public EntityView {
public:
    explicit CoinView(const logic::entities::Coin& coin);
    ~CoinView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    const logic::entities::Coin& _model;
    sf::Sprite _sprite;

    float _x = 0.0f;
    float _y = 0.0f;
    float _width = 0.0f;
    bool _isCollected = false;

    // Sprite layout constants
    static constexpr int SPRITE_SIZE = 16; // size in pixels of coin
    static constexpr int X_OFFSET = 411;   // x offset pixels on spritesheet
    static constexpr int Y_OFFSET = 313;   // y offset pixels on spritesheet

    sf::IntRect _spriteRect = {X_OFFSET, Y_OFFSET, SPRITE_SIZE, SPRITE_SIZE};

    const int _zLevel = 0; // used for rendering order of entities
};

} // namespace application

#endif // COINVIEW_H
