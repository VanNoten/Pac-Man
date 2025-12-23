#ifndef COIN_H
#define COIN_H
#include "Collectable.h"

namespace logic {

class Coin : public Collectable {
public:
    Coin(float x, float y, float width, float height);
    void collect() override;
};

} // namespace logic

#endif // COIN_H
