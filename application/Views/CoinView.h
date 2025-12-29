#ifndef COINVIEW_H
#define COINVIEW_H

#include <Entities/Coin.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Views/EntityView.h>

namespace application {

class CoinView : public EntityView {
public:
    explicit CoinView(const logic::Coin& coin);
    ~CoinView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;

private:
    const logic::Coin& _model;
    sf::Sprite _sprite;

    static constexpr int SPRITE_SIZE = 16; // size in pixels of coin
    static constexpr int X_OFFSET = 411;   // x offset pixels on spritesheet
    static constexpr int Y_OFFSET = 313;   // y offset pixels on spritesheet

    sf::IntRect _spriteRect = {X_OFFSET, Y_OFFSET, SPRITE_SIZE, SPRITE_SIZE};
};

} // namespace application

#endif // COINVIEW_H
