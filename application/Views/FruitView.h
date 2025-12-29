#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include <Entities/Fruit.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>

namespace application {

class FruitView : public EntityView {
public:
    explicit FruitView(const logic::Fruit& fruit);
    ~FruitView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;

private:
    const logic::Fruit& _model;
    sf::Sprite _sprite;

    static constexpr int SPRITE_SIZE = 36; // size in pixels of fruit
    static constexpr int X_OFFSET = 601;   // x offset pixels on spritesheet
    static constexpr int Y_OFFSET = 3;     // y offset pixels on spritesheet

    sf::IntRect _spriteRect = {X_OFFSET, Y_OFFSET, SPRITE_SIZE, SPRITE_SIZE};
};

} // namespace application

#endif // FRUITVIEW_H
