#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <Entities/Pacman.h>
#include <Views/EntityView.h>

namespace application {

class PacmanView : public EntityView {
public:
    explicit PacmanView(const logic::Pacman& pacman);
    ~PacmanView() override = default;
    void onNotify(logic::EventType event) override;
    void draw(sf::RenderWindow& window, const Camera& camera) override;

private:
    const logic::Pacman& _model;
};

} // namespace application

#endif // PACMANVIEW_H
