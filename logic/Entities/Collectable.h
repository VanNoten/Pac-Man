#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "EntityModel.h"

namespace logic {

class Collectable : public EntityModel {
public:
    Collectable(float x, float y, float width, float height);
    virtual ~Collectable() = default;
    void update(float deltaTime) override {}
    [[nodiscard]] bool isCollected() const;
    virtual void collect() = 0;
    void reset();

protected:
    bool _isCollected = false;
};

} // namespace logic

#endif // COLLECTABLE_H
