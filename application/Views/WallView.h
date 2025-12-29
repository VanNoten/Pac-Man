#ifndef WALLVIEW_H
#define WALLVIEW_H

#include <Entities/Wall.h>
#include <Views/EntityView.h>

namespace application {

class WallView : public EntityView {
public:
    explicit WallView(const logic::Wall& wall);
    ~WallView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera, float deltaTime) override;

private:
    const logic::Wall& _model;
};

} // namespace application

#endif // WALLVIEW_H
