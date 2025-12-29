#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include <Entities/Ghost.h>
#include <Views/EntityView.h>

namespace application {

class GhostView : public EntityView {
public:
    explicit GhostView(const logic::Ghost& ghost);
    ~GhostView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera) override;

private:
    logic::GhostType _ghostType;
    const logic::Ghost& _model;
};

} // namespace application

#endif // GHOSTVIEW_H
