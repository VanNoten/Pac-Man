#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H
#include "Util/Structs.h"

#include <Observer/Subject.h>

namespace logic {

class EntityModel : public Subject {
public:
    virtual ~EntityModel() = default;
    virtual void update(float deltaTime) = 0;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] virtual float getWidth() const;
    [[nodiscard]] virtual float getHeight() const;
    [[nodiscard]] Bounds getBounds() const;

protected:
    EntityModel(float x, float y, float width, float height);
    float _x = 0;
    float _y = 0;
    float _width = 0;
    float _height = 0;
};

} // namespace logic

#endif // ENTITYMODEL_H
