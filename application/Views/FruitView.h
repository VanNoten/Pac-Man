#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include <Entities/Fruit.h>
#include <Views/EntityView.h>

namespace application {

class FruitView : public EntityView {
public:
    explicit FruitView(const logic::Fruit& fruit);
    ~FruitView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera) override;

private:
    const logic::Fruit& _model;
};

} // namespace application

#endif // FRUITVIEW_H
