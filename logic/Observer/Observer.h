#ifndef OBSERVER_H
#define OBSERVER_H

namespace logic {

enum class EventType { Move, CoinCollected, FruitCollected, GhostEaten };

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(EventType event) = 0;
};

} // namespace logic

#endif // OBSERVER_H
