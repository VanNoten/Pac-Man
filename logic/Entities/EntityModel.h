#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

namespace logic {

class EntityModel {
public:
    virtual ~EntityModel() = default;
    virtual void update(float deltaTime) = 0;
    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] virtual float getWidth() const = 0;
    [[nodiscard]] virtual float getHeight() const = 0;

protected:
    EntityModel(float x, float y);
    float _x;
    float _y;
};

} // namespace logic

#endif // ENTITYMODEL_H
