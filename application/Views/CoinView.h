#ifndef COINVIEW_H
#define COINVIEW_H

#include <Entities/Coin.h>
#include <Views/EntityView.h>

namespace application {

class CoinView : public EntityView {
public:
    explicit CoinView(const logic::Coin& coin);
    ~CoinView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera) override;

private:
    const logic::Coin& _model;
};

} // namespace application

#endif // COINVIEW_H
