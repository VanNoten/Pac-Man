#ifndef FRUIT_H
#define FRUIT_H
#include "Collectable.h"

namespace logic {

class Fruit : public Collectable {
public:
    Fruit(float x, float y, float width, float height);
    void collect() override;
};

} // namespace logic

#endif // FRUIT_H
