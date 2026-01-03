#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include <Entities/Fruit.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>

namespace application::views {

/**
 * @brief Renders Fruit entities
 *
 * Concrete implementation of EntityView for Fruit entity
 */
class FruitView : public EntityView {
public:
    explicit FruitView(const logic::entities::Fruit& fruit);
    ~FruitView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    const logic::entities::Fruit& _model;
    sf::Sprite _sprite;

    float _x = 0.0f;
    float _y = 0.0f;
    float _width = 0.0f;
    bool _isCollected = false;

    // Sprite layout constants
    static constexpr int SPRITE_SIZE = 36; // size in pixels of fruit
    static constexpr int X_OFFSET = 601;   // x offset pixels on spritesheet
    static constexpr int Y_OFFSET = 153;   // y offset pixels on spritesheet

    sf::IntRect _spriteRect = {X_OFFSET, Y_OFFSET, SPRITE_SIZE, SPRITE_SIZE};

    const int _zLevel = 0; // used for rendering order of entities
};

} // namespace application::views

#endif // FRUITVIEW_H
