#ifndef WALLVIEW_H
#define WALLVIEW_H

#include <Entities/Wall.h>
#include <Views/EntityView.h>

namespace application::views {

/**
 * @brief Renders Wall entities as blue rectangles
 *
 * Concrete implementation of EntityView for Wall entity
 */
class WallView : public EntityView {
public:
    explicit WallView(const logic::entities::Wall& wall);
    ~WallView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;
    [[nodiscard]] int getZLevel() const override;

private:
    const logic::entities::Wall& _model;
    const int _zLevel = 0; // used for rendering order of entities
};

} // namespace application::views

#endif // WALLVIEW_H
